#pragma once

#include "Tourqe/Window/Window.h"
#include "Tourqe/Renderer/GraphicsContext.h"
#include "glfw/glfw3.h"

namespace TourqeE {
	class WindowsWindow : public Window
	{
	private:
		struct WindowData
		{
			std::string Title;
			uint Width, Height;
			bool VSync;
			EventCallbackFuntion EventCallbackFn;
		};
	public:
		WindowsWindow(const WindowPropeties& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		inline uint GetWidth() const override { return m_w_Data.Width; }
		inline uint GetHeight() const override { return m_w_Data.Height; }

		virtual void SetEventCallback(const EventCallbackFuntion& callback) override { m_w_Data.EventCallbackFn = callback; }
		virtual void SetVsync(bool enabled) override;
		virtual bool IsVsync() const;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowPropeties& props);
		virtual void Shutdown();

		GraphicsContext* m_Context;
		GLFWwindow* m_Window;
		GLFWmonitor* m_Monitor;
		WindowData m_w_Data;
	};
}