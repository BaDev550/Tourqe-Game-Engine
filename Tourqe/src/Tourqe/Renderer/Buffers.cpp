#include "tupch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffers.h"

namespace TourqeE {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::CurrentAPI())
		{
		case RenderAPI::None: TU_ENGINE_ASSERT(false, "RenderAPI::None not suported"); return NULL;
		case RenderAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		default:
			TU_ENGINE_ASSERT(false, "Incorrect Render API Tourqe engine only supports OpenGL for now");
			return NULL;
		}
		return NULL;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::CurrentAPI())
		{
		case RenderAPI::None: TU_ENGINE_ASSERT(false, "RenderAPI::None not suported"); return NULL;
		case RenderAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		default:
			TU_ENGINE_ASSERT(false, "Incorrect Render API Tourqe engine only supports OpenGL for now");
			return NULL;
		}
		return NULL;
	}
}