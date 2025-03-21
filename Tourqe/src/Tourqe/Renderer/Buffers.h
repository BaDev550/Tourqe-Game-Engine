#pragma once

#include "Tourqe/Application/Logger.h"
namespace TourqeE {

	enum class ShaderDataType : uint8_t {
		None = 0,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4,
		Int,
		Bool
	};
#define TDT_FLOAT ShaderDataType::Float
#define TDT_INT ShaderDataType::Int
#define TDT_BOOL ShaderDataType::Bool
#define TDT_VEC2 ShaderDataType::Vec2
#define TDT_VEC3 ShaderDataType::Vec3
#define TDT_VEC4 ShaderDataType::Vec4
#define TDT_MAT3 ShaderDataType::Mat3
#define TDT_MAT4 ShaderDataType::Mat4
	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::None: return 0;
			case TDT_FLOAT: return 4;
			case TDT_VEC2:  return 4 * 2;
			case TDT_VEC3:  return 4 * 3;
			case TDT_VEC4:  return 4 * 4;
			case TDT_MAT3:  return 4 * 3 * 3;
			case TDT_MAT4:  return 4 * 4 * 4;
			case TDT_INT:   return 4;
			case TDT_BOOL:  return 4;
		default:
			TU_ENGINE_ASSERT(false, "Wrong ShaderDataType");
			return 0;
		}
		return 0;
	}

	struct BufferElement{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() {}
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{ 	}

		uint32_t GetComponentCount() const {
			switch (Type)
			{
				case ShaderDataType::None: return 0;
				case TDT_FLOAT: return 1;
				case TDT_VEC2:  return 2;
				case TDT_VEC3:  return 3;
				case TDT_VEC4:  return 4;
				case TDT_MAT3:  return 3 * 3;
				case TDT_MAT4:  return 4 * 4;
				case TDT_INT:   return 1;
				case TDT_BOOL:  return 1;
			default:
				TU_ENGINE_ASSERT(false, "Wrong ShaderDataType");
				return 0;
			}
			return 0;
		}
	};
	class BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements) 
			: m_Elements(elements) {
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetAndStride() {
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements) {
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	class VertexBuffer {
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}