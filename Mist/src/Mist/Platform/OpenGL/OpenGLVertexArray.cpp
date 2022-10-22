#include "mstpch.h"
#include "OpenGLVertexArray.h"

#include <glad\glad.h>

namespace Mist {

	static GLenum ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::None: return NULL;
		case ShaderDataType::Bool: return GL_BOOL;
		case ShaderDataType::Int: return GL_INT;
		case ShaderDataType::Uint: return GL_UNSIGNED_INT;
		case ShaderDataType::Float: return GL_FLOAT;
		case ShaderDataType::Double: return GL_DOUBLE;
		case ShaderDataType::Vec2b: return GL_BOOL;
		case ShaderDataType::Vec3b: return GL_BOOL;
		case ShaderDataType::Vec4b: return GL_BOOL;
		case ShaderDataType::Vec2i: return GL_INT;
		case ShaderDataType::Vec3i: return GL_INT;
		case ShaderDataType::Vec4i: return GL_INT;
		case ShaderDataType::Vec2u: return GL_UNSIGNED_INT;
		case ShaderDataType::Vec3u: return GL_UNSIGNED_INT;
		case ShaderDataType::Vec4u: return GL_UNSIGNED_INT;
		case ShaderDataType::Vec2f: return GL_FLOAT;
		case ShaderDataType::Vec3f: return GL_FLOAT;
		case ShaderDataType::Vec4f: return GL_FLOAT;
		case ShaderDataType::Vec2d: return GL_DOUBLE;
		case ShaderDataType::Vec3d: return GL_DOUBLE;
		case ShaderDataType::Vec4d: return GL_DOUBLE;
		case ShaderDataType::Mat2x2: return GL_FLOAT;
		case ShaderDataType::Mat2x3: return GL_FLOAT;
		case ShaderDataType::Mat2x4: return GL_FLOAT;
		case ShaderDataType::Mat3x2: return GL_FLOAT;
		case ShaderDataType::Mat3x3: return GL_FLOAT;
		case ShaderDataType::Mat3x4: return GL_FLOAT;
		case ShaderDataType::Mat4x2: return GL_FLOAT;
		case ShaderDataType::Mat4x3: return GL_FLOAT;
		case ShaderDataType::Mat4x4: return GL_FLOAT;
		}

		MST_CORE_ASSERT(false, "Invalid ShaderDataType! (ShaderDataTypeToGLBaseType)");
		return NULL;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		MST_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "VertexBuffer has no BufferLayout! (OpenGLVertexArray::AddVertexBuffer)");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToGLBaseType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}