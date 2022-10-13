#include "mstpch.h"
#include "Application.h"

#include "Events\ApplicationEvent.h"
#include "Log.h"

namespace Mist {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			MST_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			MST_TRACE(e);
		}

		while (true);
	}

}