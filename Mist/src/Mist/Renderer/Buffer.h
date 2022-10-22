#pragma once

namespace Mist {

	enum class ShaderDataType
	{
		None = 0,
		Bool, Int, Uint, Float, Double,
		Vec2b, Vec3b, Vec4b,
		Vec2i, Vec3i, Vec4i,
		Vec2u, Vec3u, Vec4u,
		Vec2f, Vec3f, Vec4f,
		Vec2d, Vec3d, Vec4d,
		Mat2x2, Mat2x3, Mat2x4,
		Mat3x2, Mat3x3, Mat3x4,
		Mat4x2, Mat4x3, Mat4x4
	}; 

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None: return 0;
		case ShaderDataType::Bool: return 1;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Uint: return 4;
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Double: return 4;
		case ShaderDataType::Vec2b: return 1 * 2;
		case ShaderDataType::Vec3b: return 1 * 3;
		case ShaderDataType::Vec4b: return 1 * 4;
		case ShaderDataType::Vec2i: return 4 * 2;
		case ShaderDataType::Vec3i: return 4 * 3;
		case ShaderDataType::Vec4i: return 4 * 4;
		case ShaderDataType::Vec2u: return 4 * 2;
		case ShaderDataType::Vec3u: return 4 * 3;
		case ShaderDataType::Vec4u: return 4 * 4;
		case ShaderDataType::Vec2f: return 4 * 2;
		case ShaderDataType::Vec3f: return 4 * 3;
		case ShaderDataType::Vec4f: return 4 * 4;
		case ShaderDataType::Vec2d: return 4 * 2;
		case ShaderDataType::Vec3d: return 4 * 3;
		case ShaderDataType::Vec4d: return 4 * 4;
		case ShaderDataType::Mat2x2: return 4 * 2 * 2;
		case ShaderDataType::Mat2x3: return 4 * 2 * 3;
		case ShaderDataType::Mat2x4: return 4 * 2 * 4;
		case ShaderDataType::Mat3x2: return 4 * 3 * 2;
		case ShaderDataType::Mat3x3: return 4 * 3 * 3;
		case ShaderDataType::Mat3x4: return 4 * 3 * 4;
		case ShaderDataType::Mat4x2: return 4 * 4 * 2;
		case ShaderDataType::Mat4x3: return 4 * 4 * 3;
		case ShaderDataType::Mat4x4: return 4 * 4 * 4;
		}

		MST_CORE_ASSERT(false, "Invalid ShaderDataType! (ShaderDataTypeSize)");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case ShaderDataType::None: return 0;
			case ShaderDataType::Bool: return 1;
			case ShaderDataType::Int: return 1;
			case ShaderDataType::Uint: return 1;
			case ShaderDataType::Float: return 1;
			case ShaderDataType::Double: return 1;
			case ShaderDataType::Vec2b: return 2;
			case ShaderDataType::Vec3b: return 3;
			case ShaderDataType::Vec4b: return 4;
			case ShaderDataType::Vec2i: return 2;
			case ShaderDataType::Vec3i: return 3;
			case ShaderDataType::Vec4i: return 4;
			case ShaderDataType::Vec2u: return 2;
			case ShaderDataType::Vec3u: return 3;
			case ShaderDataType::Vec4u: return 4;
			case ShaderDataType::Vec2f: return 2;
			case ShaderDataType::Vec3f: return 3;
			case ShaderDataType::Vec4f: return 4;
			case ShaderDataType::Vec2d: return 2;
			case ShaderDataType::Vec3d: return 3;
			case ShaderDataType::Vec4d: return 4;
			case ShaderDataType::Mat2x2: return 2 * 2;
			case ShaderDataType::Mat2x3: return 2 * 3;
			case ShaderDataType::Mat2x4: return 2 * 4;
			case ShaderDataType::Mat3x2: return 3 * 2;
			case ShaderDataType::Mat3x3: return 3 * 3;
			case ShaderDataType::Mat3x4: return 3 * 4;
			case ShaderDataType::Mat4x2: return 4 * 2;
			case ShaderDataType::Mat4x3: return 4 * 3;
			case ShaderDataType::Mat4x4: return 4 * 4;
			}

			MST_CORE_ASSERT(false, "Invalid ShaderDataType! (BufferElement::GetComponentCount)");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: m_Elements(elements)
		{
			CalculateOffsetsAndStride();
		}

		BufferLayout() {}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}

		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}