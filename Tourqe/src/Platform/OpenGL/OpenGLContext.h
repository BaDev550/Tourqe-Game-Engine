#pragma once

#include "Tourqe/TCore.h"
#include "Tourqe/Renderer/GraphicsContext.h"

namespace TourqeE {
	class OpenGLContext : public GraphicsContext
	{
	public:
		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}
