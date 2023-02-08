#include "SnowflakePCH.h"
#include "OpenGLShader.h"

#include "Files/FileSystem.h"

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Snowflake
{
    namespace ShaderUtils
    {
        GLenum GetShaderTypeFromString(const std::string& ShaderType)
        {
            if (ShaderType == "vertex") return GL_VERTEX_SHADER;
            if (ShaderType == "fragment" || ShaderType == "pixel") return GL_FRAGMENT_SHADER;

            ENGINE_ASSERT(false, "Failed to get shader type from string! Unknown shader type!")
            return 0;
        }
    }
    
    OpenGLShader::OpenGLShader(const std::filesystem::path& Filepath)
        : m_Filepath(Filepath)
    {
        std::string ShaderSource = FileSystem::ReadFile(Filepath);
        auto ShaderSources = PreProcessShader(ShaderSource);
        Compile(ShaderSources);
        
        // Get shader name from filepath
        m_Name = Filepath.stem().string();
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_ShaderProgram);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_ShaderProgram);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& UniformName, int Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform1i(UniformLocation, Value);
    }

    void OpenGLShader::SetIntArray(const std::string& UniformName, int* Values, uint32_t ValueCount)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform1iv(UniformLocation, ValueCount, Values);
    }

    void OpenGLShader::SetFloat(const std::string& UniformName, float Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform1f(UniformLocation, Value);
    }

    void OpenGLShader::SetVector2(const std::string& UniformName, const glm::vec2& Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform2f(UniformLocation, Value.x, Value.y);
    }

    void OpenGLShader::SetVector3(const std::string& UniformName, const glm::vec3& Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform3f(UniformLocation, Value.x, Value.y, Value.z);
    }

    void OpenGLShader::SetVector4(const std::string& UniformName, const glm::vec4& Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniform4f(UniformLocation, Value.x, Value.y, Value.z, Value.w);
    }

    void OpenGLShader::SetMatrix4(const std::string& UniformName, const glm::mat4& Value)
    {
        int UniformLocation = glGetUniformLocation(m_ShaderProgram, UniformName.c_str());
        glUniformMatrix4fv(UniformLocation, 1, GL_FALSE, glm::value_ptr(Value));
    }

    /*-------------------------*/
    /* -- Utility Functions -- */
    /*-------------------------*/

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcessShader(const std::string& ShaderSource)
    {
        std::unordered_map<GLenum, std::string> ShaderSources;

        const char* ShaderTypeToken = "#type";
        size_t ShaderTypeTokenLength = strlen(ShaderTypeToken);
        size_t Pos = ShaderSource.find(ShaderTypeToken, 0); // Start of shader type declaration line
        while (Pos != std::string::npos)
        {
            size_t EOL = ShaderSource.find_first_of("\r\n", Pos); // End of shader type declaration line
            ENGINE_ASSERT(EOL != std::string::npos, "Syntax error")
            
            size_t Begin = Pos + ShaderTypeTokenLength + 1; // Start of shader type name (after "#type " keyword)
            std::string ShaderType = ShaderSource.substr(Begin, EOL - Begin);
            ENGINE_ASSERT(ShaderUtils::GetShaderTypeFromString(ShaderType), "Invalid shader type specified")

            size_t NextLinePos = ShaderSource.find_first_not_of("\r\n", EOL); // Start of shader code after shader type declaration line
            ENGINE_ASSERT(NextLinePos != std::string::npos, "Syntax error")
            Pos = ShaderSource.find(ShaderTypeToken, NextLinePos); // Start of next shader type declaration line

            ShaderSources[ShaderUtils::GetShaderTypeFromString(ShaderType)] = (Pos == std::string::npos) ? ShaderSource.substr(NextLinePos) :
                ShaderSource.substr(NextLinePos, Pos - NextLinePos);
        }

        return ShaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
    {
        GLuint ShaderProgram = glCreateProgram();
        ENGINE_ASSERT(ShaderSources.size() <= 2, "Failed to compile shaders! Only 2 shader types can be compiled at once!")

        std::array<GLenum, 2> GLShaderIDs;
        int GLShaderIDIndex = 0;

        for (auto& KV : ShaderSources)
        {
            GLenum ShaderType = KV.first;
            const std::string& ShaderSource = KV.second;
            const GLchar* ShaderSourceCStr = ShaderSource.c_str();

            GLuint ShaderHandle = glCreateShader(ShaderType);
            glShaderSource(ShaderHandle, 1, &ShaderSourceCStr, 0);
            glCompileShader(ShaderHandle);

            // Check if the shader compiled successfully. If there are compilation errors, we log them.
            GLint WasShaderCompilationSuccessful = 0;
            glGetShaderiv(ShaderHandle, GL_COMPILE_STATUS, &WasShaderCompilationSuccessful);
            if (WasShaderCompilationSuccessful == GL_FALSE)
            {
                GLint MaxLength = 0;
                glGetShaderiv(ShaderHandle, GL_INFO_LOG_LENGTH, &MaxLength);

                std::vector<GLchar> ShaderInfoLog(MaxLength);
                glGetShaderInfoLog(ShaderHandle, MaxLength, &MaxLength, &ShaderInfoLog[0]);

                glDeleteShader(ShaderHandle);

                ENGINE_LOG_ERROR_TAG("Renderer", "Failed to compile shader '{}'!", m_Name);
                ENGINE_LOG_ERROR_TAG("Renderer", "Shader Error: {}", ShaderInfoLog.data());
                break;
            }

            glAttachShader(ShaderProgram, ShaderHandle);
            GLShaderIDs[GLShaderIDIndex++] = ShaderHandle;
        }

        m_ShaderProgram = ShaderProgram;

        glLinkProgram(ShaderProgram);

        GLint IsShaderProgramLinked = 0;
        glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &IsShaderProgramLinked);
        if (IsShaderProgramLinked == GL_FALSE)
        {
            GLint MaxLength = 0;
            glGetProgramiv(ShaderProgram, GL_INFO_LOG_LENGTH, &MaxLength);

            std::vector<GLchar> ProgramInfoLog(MaxLength);
            glGetProgramInfoLog(ShaderProgram, MaxLength, &MaxLength, &ProgramInfoLog[0]);

            glDeleteProgram(ShaderProgram);

            for (auto ShaderID : GLShaderIDs)
                glDeleteShader(ShaderID);

            ENGINE_LOG_ERROR_TAG("Renderer", "Failed to link shader program!");
            ENGINE_LOG_ERROR_TAG("Renderer", "Link Error: {}", ProgramInfoLog.data());
            return;
        }

        for (auto ShaderID : GLShaderIDs)
        {
            glDetachShader(m_ShaderProgram, ShaderID);
            glDeleteShader(ShaderID);
        }
    }
}
