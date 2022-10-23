#include "mstpch.h"
#include "Buffer.h"

#include "Mist\Platform\OpenGL\OpenGLBuffer.h"
#include "Renderer.h"

namespace Mist {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::API::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::API::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (VertexBuffer::Create)"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (VertexBuffer::Create)");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::API::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::API::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (IndexBuffer::Create)"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (IndexBuffer::Create)");
		return nullptr;
	}

}
