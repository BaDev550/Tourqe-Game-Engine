#include "tupch.h"
#include "Application.h"

#include "Tourqe/Input/Input.h"
#include "Tourqe/Application/Logger.h"
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

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float vertices[3 * 3] = {
			-0.5f, -0.5f ,0.0f,
			 0.5f, -0.5f ,0.0f,
			 0.0f,  0.5f ,0.0f,
		};
		m_VertexBuffer.reset(CreateVertexBuffer(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		unsigned int indices[3] = {
			0, 1, 2
		};
		m_IndexBuffer.reset(CreateIndexBuffer(indices, sizeof(indices)));
		m_IndexBuffer->Bind();

		glBindVertexArray(0);

		std::string vertexSource = R"(
			#version 330 core
			layout(location = 0) in vec3 aPos;
			out vec3 pos;

			void main(){
				pos = aPos;
				gl_Position = vec4(aPos, 1.0f);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			out vec4 FragColor;
			in vec3 pos;

			void main(){
				FragColor = vec4(pos * 0.5f + 0.5f, 1.0f);
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
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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