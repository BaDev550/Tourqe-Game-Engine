#include "tupch.h"
#include "VertexArrayBuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArrayBuffer.h"

namespace TourqeE {

	VertexArrayBuffer* VertexArrayBuffer::Create()
	{
		switch (Renderer::CurrentAPI())
		{
		case RenderAPI::None: TU_ENGINE_ASSERT(false, "RenderAPI::None not suported"); return NULL;
		case RenderAPI::OpenGL: return new OpenGLVertexArrayBuffer();
		default:
			TU_ENGINE_ASSERT(false, "Incorrect Render API Tourqe engine only supports OpenGL for now");
			return NULL;
		}
		return NULL;
	}

}