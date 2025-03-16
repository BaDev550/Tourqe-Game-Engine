#pragma once

#include "Tourqe/TCore.h"
#include "Tourqe/Application/Logger.h"
#include "Tourqe/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace TourqeE {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
