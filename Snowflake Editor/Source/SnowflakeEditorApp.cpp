#include "Application/ApplicationEntryPoint.h"

#include "GameCore/Camera/OrthographicCamera.h"

#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"

#include <imgui.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Snowflake
{
    class SnowflakeEditorLayer : public Layer
    {
    public:
        SnowflakeEditorLayer()
            : Layer("Snowflake Editor"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {}

        void OnAttach() override
        {
			// Render a triangle
			float TriangleVertices[9] =
			{
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};

			uint32_t TriangleIndices[3] =
			{
				0, 1, 2
			};

			BufferLayout TriangleVertexBufferLayout =
			{
				{ ShaderDataType::Float3, "a_Position" }
			};

			m_TriangleShader = Shader::CreateShader("Resources/Shaders/OpenGL/TriangleShader.glsl");

			m_TriangleVertexArray = VertexArray::CreateVertexArray();

			m_TriangleVertexBuffer = VertexBuffer::CreateVertexBuffer(TriangleVertices, sizeof(TriangleVertices));
			m_TriangleVertexBuffer->SetBufferLayout(TriangleVertexBufferLayout);

			m_TriangleIndexBuffer = IndexBuffer::CreateIndexBuffer(TriangleIndices, sizeof(TriangleIndices));

			m_TriangleVertexArray->AddVertexBuffer(m_TriangleVertexBuffer);
			m_TriangleVertexArray->SetIndexBuffer(m_TriangleIndexBuffer);

            // Render a square
            float SquareVertices[12] =
            {
				-0.75f, -0.75f, 0.0f,
			     0.75f, -0.75f, 0.0f,
			     0.75f,  0.75f, 0.0f,
			    -0.75f,  0.75f, 0.0f
            };

            uint32_t SquareIndices[6] =
            {
                0, 1, 2, 2, 3, 0
            };

			BufferLayout SquareVertexBufferLayout =
			{
				{ ShaderDataType::Float3, "a_Position" }
			};

            m_SquareShader = Shader::CreateShader("Resources/Shaders/OpenGL/SquareShader.glsl");

            m_SquareVertexArray = VertexArray::CreateVertexArray();

            m_SquareVertexBuffer = VertexBuffer::CreateVertexBuffer(SquareVertices, sizeof(SquareVertices));
            m_SquareVertexBuffer->SetBufferLayout(SquareVertexBufferLayout);

            m_SquareIndexBuffer = IndexBuffer::CreateIndexBuffer(SquareIndices, sizeof(SquareIndices));
            
            m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
            m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);
        }

        void OnUpdate() override
        {
			m_TriangleShader->Bind();
			m_TriangleShader->SetMatrix4("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
			m_TriangleVertexArray->Bind();
			Renderer::DrawIndexed(m_TriangleIndexBuffer->GetCount(), PrimitiveType::Triangles);

			m_SquareShader->Bind();
			m_SquareShader->SetMatrix4("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
			m_SquareVertexArray->Bind();
			Renderer::DrawIndexed(m_SquareIndexBuffer->GetCount(), PrimitiveType::Triangles);
        }

        void OnUIRender() override
        {
            ImGui::Begin("Camera Controls");
            
            glm::vec3 CameraPosition = m_Camera.GetPosition();
            if (ImGui::SliderFloat3("Position", glm::value_ptr(CameraPosition), 0.0f, 100.0f, "%.2f"))
                m_Camera.SetPosition(CameraPosition);

            ImGui::NewLine();

            float CameraRotation = m_Camera.GetRotation();
            if (ImGui::SliderFloat("Rotation", &CameraRotation, 0.0f, 180.0f, "%.2f"))
                m_Camera.SetRotation(CameraRotation);

            ImGui::End();
        }

    private:
		Ref<Shader> m_TriangleShader;
		Ref<VertexArray> m_TriangleVertexArray;
		Ref<VertexBuffer> m_TriangleVertexBuffer;
		Ref<IndexBuffer> m_TriangleIndexBuffer;

		Ref<Shader> m_SquareShader;
		Ref<VertexArray> m_SquareVertexArray;
		Ref<VertexBuffer> m_SquareVertexBuffer;
		Ref<IndexBuffer> m_SquareIndexBuffer;

        OrthographicCamera m_Camera;
    };
    
    class SnowflakeEditorApp : public Application
    {
    public:
        SnowflakeEditorApp(const ApplicationSpecification& AppSpecification)
            : Application(AppSpecification) {}

        void OnInitialize() override
        {
            PushLayer(new SnowflakeEditorLayer());
        }
    };

    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments)
    {
        ApplicationSpecification SnowflakeEditorAppSpecification;
        SnowflakeEditorAppSpecification.Name = "Snowflake Editor";
        SnowflakeEditorAppSpecification.CommandLineArguments = CommandLineArguments;
        
        return new SnowflakeEditorApp(SnowflakeEditorAppSpecification);
    }
}