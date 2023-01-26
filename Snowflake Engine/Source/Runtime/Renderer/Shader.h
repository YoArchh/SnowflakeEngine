#pragma once

#include <filesystem>

#include <glm/glm.hpp>

namespace Snowflake
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const std::string& UniformName, int Value) = 0;
        virtual void SetIntArray(const std::string& UniformName, int* Values, uint32_t ValueCount) = 0;

        virtual void SetFloat(const std::string& UniformName, float Value) = 0;
        virtual void SetVector2(const std::string& UniformName, const glm::vec2& Value) = 0;
        virtual void SetVector3(const std::string& UniformName, const glm::vec3& Value) = 0;
        virtual void SetVector4(const std::string& UniformName, const glm::vec4& Value) = 0;

        virtual void SetMatrix4(const std::string& UniformName, const glm::mat4& Value) = 0;

        static Ref<Shader> CreateShader(const std::filesystem::path& Filepath);
    };
}
