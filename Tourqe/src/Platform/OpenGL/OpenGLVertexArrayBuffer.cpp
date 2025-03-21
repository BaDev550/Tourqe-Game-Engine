#include "tupch.h"
#include "OpenGLVertexArrayBuffer.h"
#include "glad/glad.h"

namespace TourqeE {
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case TDT_FLOAT: return GL_FLOAT;
		case TDT_VEC2:  return GL_FLOAT;
		case TDT_VEC3:  return GL_FLOAT;
		case TDT_VEC4:  return GL_FLOAT;
		case TDT_MAT3:  return GL_FLOAT;
		case TDT_MAT4:  return GL_FLOAT;
		case TDT_INT:   return GL_INT;
		case TDT_BOOL:  return GL_BOOL;
		default:
			TU_ENGINE_ASSERT(false, "Wrong ShaderDataType");
			return 0;
		}
		return 0;
	}

	OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer() {
		glCreateVertexArrays(1, &m_BufferID);
	}

	void OpenGLVertexArrayBuffer::Bind() const
	{
		glBindVertexArray(m_BufferID);
	}

	void OpenGLVertexArrayBuffer::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArrayBuffer::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		TU_ENGINE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");
		glBindVertexArray(m_BufferID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset
			);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArrayBuffer::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_BufferID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}