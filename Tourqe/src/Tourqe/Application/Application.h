#pragma once

#include "Tourqe/TCore.h"

#include "Tourqe/Window/Window.h"
#include "Tourqe/Window/LayerStack.h"
#include "Tourqe/Window/ImGui/ImGuiLayer.h"

#include "Tourqe/Events/ApplicationEvent.h"

#include "Tourqe/Renderer/Shader.h"
#include "Tourqe/Renderer/Buffers.h"

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

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool m_Running = true;

		static Application* s_Instance;

	private:
		unsigned int VAO;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	Application* CreateApplication();
}
