#pragma once

namespace Mist {

	enum class RendererAPI
	{
		None = 0,
		OpenGL, Vulkan, DirectX
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};

}