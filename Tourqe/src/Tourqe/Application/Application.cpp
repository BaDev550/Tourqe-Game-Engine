#include "tupch.h"
#include "Application.h"

#include "Tourqe/Input/Input.h"
#include "Tourqe/Application/Logger.h"
#include <glad/glad.h>

namespace TourqeE {
	Application* Application::s_Instance = NULL;

	Application::Application()
	{
		TU_ENGINE_ASSERT(!s_Instance, "Application allready exixts");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(TU_BIND_EVENT_FUNCTION(Application::OnEvent));
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
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}