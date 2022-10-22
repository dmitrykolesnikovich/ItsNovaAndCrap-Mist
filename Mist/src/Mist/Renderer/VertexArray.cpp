#include "mstpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Mist\Platform\OpenGL\OpenGLVertexArray.h"

namespace Mist {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::Vulkan: MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::DirectX: MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (VertexArray::Create)"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (VertexArray::Create)");
		return nullptr;
	}

}