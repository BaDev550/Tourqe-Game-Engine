#pragma once

#include "Tourqe/TCore.h"

#include "Tourqe/Window/Window.h"
#include "Tourqe/Window/LayerStack.h"

#include "Tourqe/Events/ApplicationEvent.h"

namespace TourqeE {

	class TOURQE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;

		static Application* s_Instance;
	};

	Application* CreateApplication();
}
