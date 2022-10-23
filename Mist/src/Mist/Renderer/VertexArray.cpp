#include "mstpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Mist\Platform\OpenGL\OpenGLVertexArray.h"

namespace Mist {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::API::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::API::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (VertexArray::Create)");
		return nullptr;
	}

}