#include "tupch.h"
#include "WindowsWindow.h"

#include "Tourqe/Application/Logger.h"

namespace TourqeE {
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowPropeties& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowPropeties& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_w_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVsync() const
	{
		return m_w_Data.VSync;
	}

	void WindowsWindow::Init(const WindowPropeties& props)
	{
		m_w_Data.Title = props.Title;
		m_w_Data.Width = props.Width;
		m_w_Data.Height = props.Height;
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			TU_ENGINE_ASSERT(success, "GLFW Init failed");

			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_w_Data.Width, (int)m_w_Data.Height, m_w_Data.Title.c_str(), NULL, NULL);
		TU_ENGINE_ASSERT(m_Window != NULL, "Window Creation Failed");
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_w_Data);
		SetVsync(true);

		TU_ENGINE_INFO("Window Created");
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
}