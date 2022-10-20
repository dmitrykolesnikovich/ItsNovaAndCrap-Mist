#include "mstpch.h"
#include "Buffer.h"

#include "Mist\Platform\OpenGL\OpenGLBuffer.h"
#include "Renderer.h"

namespace Mist {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (VertexBuffer::Create)");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (IndexBuffer::Create)");
		return nullptr;
	}

}
