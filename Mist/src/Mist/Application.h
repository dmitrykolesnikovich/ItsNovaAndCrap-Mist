#pragma once

#include "Core.h"

#include "Window.h"
#include "Mist\LayerStack.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"

namespace Mist {

	class MIST_API Application
	{
	public:
		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in client
	Application* CreateApplication();

}
