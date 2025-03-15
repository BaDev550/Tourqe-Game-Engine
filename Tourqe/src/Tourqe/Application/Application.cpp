#include "tupch.h"
#include "Application.h"

#include "Tourqe/Application/Logger.h"

namespace TourqeE {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running) {
			m_Window->OnUpdate();
		}
	}
}