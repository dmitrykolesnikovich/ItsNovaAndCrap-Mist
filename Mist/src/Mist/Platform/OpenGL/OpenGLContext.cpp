#include "mstpch.h"
#include "OpenGLContext.h"

namespace Mist {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MST_CORE_ASSERT(status, "Couldn't Initialize Glad!");

		MST_CORE_INFO("OpenGL Info: ");
		MST_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		MST_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		MST_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}