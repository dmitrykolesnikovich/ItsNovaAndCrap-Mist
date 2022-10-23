#pragma once

#include "Core.h"

#include "Window.h"
#include "Mist\LayerStack.h"
#include "Events\Event.h"
#include "Events\ApplicationEvent.h"
#include "Mist\ImGui\ImGuiLayer.h"
#include "Mist\Renderer\Shader.h"
#include "Mist\Renderer\Buffer.h"
#include "Mist\Renderer\VertexArray.h"
#include "Mist\Renderer\OrthographicCamera.h"

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

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		OrthographicCamera m_Camera;
	};

	// To be defined in client
	Application* CreateApplication();

}
