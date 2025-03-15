#pragma once

#include "Tourqe/TCore.h"
#include "Tourqe/Events/ApplicationEvent.h"

#include "Tourqe/Window.h"

namespace TourqeE {

	class TOURQE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}
