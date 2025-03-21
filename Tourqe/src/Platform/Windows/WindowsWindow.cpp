#include "tupch.h"
#include "WindowsWindow.h"

#include "Tourqe/Events/ApplicationEvent.h"
#include "Tourqe/Events/KeyEvent.h"
#include "Tourqe/Events/MouseEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace TourqeE {
	static bool s_GLFWInitialized = false;
	static void GLFWErrorCallback(int err, const char* desc);

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
		m_Context->SwapBuffers();
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
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_w_Data.Width, (int)m_w_Data.Height, m_w_Data.Title.c_str(), NULL, NULL);
		TU_ENGINE_ASSERT(m_Window != NULL, "Window Creation Failed");

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		m_Monitor = glfwGetPrimaryMonitor();
		static const GLFWvidmode* vidMode = glfwGetVideoMode(m_Monitor);
		int xpos = (vidMode->width - m_w_Data.Width) / 2;
		int ypos = (vidMode->height - m_w_Data.Height) / 2;
		glfwSetWindowPos(m_Window, xpos, ypos);
		glfwSetWindowUserPointer(m_Window, &m_w_Data);
		SetVsync(true);

		TU_ENGINE_INFO("Window Created");
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallbackFn(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallbackFn(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS: {
				KeyPressedEvent event(key, 0);
				data.EventCallbackFn(event);
				break;
			}
			case GLFW_RELEASE: {
				KeyReleasedEvent event(key);
				data.EventCallbackFn(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallbackFn(event);
				break;
			}
			default:
				TU_ENGINE_ERROR("Incorrect Key action!");
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallbackFn(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallbackFn(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallbackFn(event);
				break;
			}
			default:
				TU_ENGINE_ERROR("Incorrect Mouse action!");
				break;
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)x, (float)y);
			data.EventCallbackFn(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallbackFn(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void GLFWErrorCallback(int err, const char* desc)
	{
		TU_ENGINE_ERROR("GLFW Error [{0}]: {1}", err, desc);
	}
}