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
        glUniformMatrix3fv(UniformLocation, 1, GL_FALSE, glm::value_ptr(Value));
    }

    /*-------------------------*/
    /* -- Utility Functions -- */
    /*-------------------------*/

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcessShader(const std::string& ShaderSource)
    {
        std::unordered_map<GLenum, std::string> ShaderSources;

        const char* ShaderTypeToken = "#type";
        size_t ShaderTypeTokenLength = strlen(ShaderTypeToken);
        size_t Pos = ShaderSource.find(ShaderTypeToken, 0);
        while (Pos != std::string::npos)
        {
            size_t EOL = ShaderSource.find_first_of("\r\n", Pos);
            ENGINE_ASSERT(EOL != std::string::npos, "Failed to pre-process shader! Syntax error!")

            size_t Begin = Pos + ShaderTypeTokenLength + 1;
            std::string ShaderType = ShaderSource.substr(Begin, Begin - EOL);
            ENGINE_ASSERT(ShaderUtils::GetShaderTypeFromString(ShaderType), "Failed to pre-process shader! Invalid shader type!")

            size_t NextLinePos = ShaderSource.find_first_not_of("\r\n", EOL);
            ENGINE_ASSERT(NextLinePos != std::string::npos, "Failed to pre-process shader! Syntax error!")

            ShaderSources[ShaderUtils::GetShaderTypeFromString(ShaderType)] = Pos == std::string::npos ? ShaderSource.substr(NextLinePos)
                                                                            : ShaderSource.substr(NextLinePos, Pos - NextLinePos);
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

            // TODO: (YoArchh) Check for shader compilication errors

            glAttachShader(ShaderProgram, ShaderHandle);
            GLShaderIDs[GLShaderIDIndex++] = ShaderHandle;
        }

        m_ShaderProgram = ShaderProgram;

        glLinkProgram(ShaderProgram);

        // TODO: (YoArchh) Check for shader program linking errors.

        for (auto ShaderID : GLShaderIDs)
        {
            glDetachShader(m_ShaderProgram, ShaderID);
            glDeleteShader(ShaderID);
        }
    }
}
