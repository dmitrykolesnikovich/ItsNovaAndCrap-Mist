#pragma once

#include "Mist\Layer.h"

#include "Mist\Events\ApplicationEvent.h"
#include "Mist\Events\KeyEvent.h"
#include "Mist\Events\MouseEvent.h"

namespace Mist {

	class MIST_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	private:
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		bool OnWindowMovedEvent(WindowMovedEvent& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);
		bool OnWindowFocusEvent(WindowFocusEvent& e);
		bool OnWindowLostFocusEvent(WindowLostFocusEvent& e);
		
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);

		float m_Time = 0.0f;
	};

}
