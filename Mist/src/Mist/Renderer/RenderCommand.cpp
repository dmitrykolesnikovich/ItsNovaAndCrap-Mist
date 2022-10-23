#include "mstpch.h"
#include "RenderCommand.h"

#include "Mist\Platform\OpenGL\OpenGLRendererAPI.h"

namespace Mist {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}