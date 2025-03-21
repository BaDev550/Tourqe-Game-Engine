#include "tupch.h"
#include "Application.h"

#include "Tourqe/Input/Input.h"
#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLBuffers.h"

namespace TourqeE {
	Application* Application::s_Instance = NULL;

	Application::Application()
	{
		TU_ENGINE_ASSERT(!s_Instance, "Application allready exixts");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(TU_BIND_EVENT_FUNCTION(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArrayBuffer.reset(VertexArrayBuffer::Create());
		float vertices[3 * 7] = {
			-0.5f, -0.5f ,0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f ,0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ TDT_VEC3, "aPos" },
			{ TDT_VEC4, "aColor" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArrayBuffer->AddVertexBuffer(m_VertexBuffer);
		
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArrayBuffer->SetIndexBuffer(m_IndexBuffer);

		m_CubeVertexArrayBuffer.reset(VertexArrayBuffer::Create());
		float Cubevertices[4 * 7] = {
			-0.5f, -0.5f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  0.5f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f ,0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> CubeVBO;
		CubeVBO.reset(VertexBuffer::Create(Cubevertices, sizeof(Cubevertices)));
		CubeVBO->SetLayout(layout);
		m_CubeVertexArrayBuffer->AddVertexBuffer(CubeVBO);

		unsigned int CubeIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> CubeEBO;
		CubeEBO.reset(IndexBuffer::Create(CubeIndices, sizeof(CubeIndices) / sizeof(uint32_t)));
		m_CubeVertexArrayBuffer->SetIndexBuffer(CubeEBO);

		std::string vertexSource = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			layout(location = 1) in vec4 aColor;
			out vec4 color;
			
			void main(){
				color = aColor;
				gl_Position = vec4(aPos, 1.0f);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			out vec4 FragColor;
			in vec4 color;

			void main(){
				FragColor = color;
			}
		)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
	}
	
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(TU_BIND_EVENT_FUNCTION(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::Run()
	{
		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			m_Shader->Bind();
			m_CubeVertexArrayBuffer->Bind();
			glDrawElements(GL_TRIANGLES, m_CubeVertexArrayBuffer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_VertexArrayBuffer->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArrayBuffer->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}