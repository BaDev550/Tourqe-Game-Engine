#pragma once
#include "Tourqe/Renderer/VertexArrayBuffer.h"

namespace TourqeE {
	class OpenGLVertexArrayBuffer : public VertexArrayBuffer
	{
	public:
		OpenGLVertexArrayBuffer();
		virtual ~OpenGLVertexArrayBuffer() {}
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_BufferID;
	};
}