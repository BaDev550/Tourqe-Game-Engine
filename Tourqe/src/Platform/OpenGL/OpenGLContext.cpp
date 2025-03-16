#include "tupch.h"
#include "OpenGLContext.h"

#include "glfw/glfw3.h"
#include <glad/glad.h>

namespace TourqeE {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		TU_ENGINE_ASSERT(m_WindowHandle, "Window Handle is NULL");
	}

	void OpenGLContext::Init()
    {
		glfwMakeContextCurrent(m_WindowHandle);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		TU_ENGINE_ASSERT(status, "Failed to init GLAD");

		TU_ENGINE_INFO("|-OpenGL Info");
		TU_ENGINE_INFO("|----Renderer: {0}", (char*)glGetString(GL_RENDERER));
		TU_ENGINE_INFO("|----Vendor: {0}", (char*)glGetString(GL_VENDOR));
		TU_ENGINE_INFO("|----Version: {0}", (char*)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
		glfwSwapBuffers(m_WindowHandle);
    }
}