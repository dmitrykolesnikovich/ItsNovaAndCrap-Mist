#include "mstpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Mist\Platform\OpenGL\OpenGLShader.h"

namespace Mist {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:	MST_CORE_ASSERT(false, "RendererAPI::None is currently not supported! (Shader::Create)"); return nullptr;
		case RendererAPI::API::Vulkan:	MST_CORE_ASSERT(false, "RendererAPI::Vulkan is currently not supported! (Shader::Create)"); return nullptr;
		case RendererAPI::API::DirectX:	MST_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! (Shader::Create)"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		MST_CORE_ASSERT(false, "Invalid RendererAPI! (Shader::Create)");
		return nullptr;
	}

}
