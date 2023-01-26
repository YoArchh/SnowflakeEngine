#pragma once

#include "Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Snowflake
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::filesystem::path& Filepath);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetInt(const std::string& UniformName, int Value) override;
        virtual void SetIntArray(const std::string& UniformName, int* Values, uint32_t ValueCount) override;

        virtual void SetFloat(const std::string& UniformName, float Value) override;
        virtual void SetVector2(const std::string& UniformName, const glm::vec2& Value) override;
        virtual void SetVector3(const std::string& UniformName, const glm::vec3& Value) override;
        virtual void SetVector4(const std::string& UniformName, const glm::vec4& Value) override;

        virtual void SetMatrix4(const std::string& UniformName, const glm::mat4& Value) override;

    private:
        std::unordered_map<GLenum, std::string> PreProcessShader(const std::string& ShaderSource);
        void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);
        
    private:
        uint32_t m_ShaderProgram;
        std::filesystem::path m_Filepath;
        std::string m_Name;
    };
}
