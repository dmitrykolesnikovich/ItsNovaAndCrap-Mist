#include <Mist.h>

class ExampleLayer : public Mist::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	
	void OnUpdate() override
	{
		if (Mist::Input::IsKeyPressed(MST_KEY_TAB))
			MST_TRACE("Tab key is pressed!! (OnUpdate)");
	}

	void OnEvent(Mist::Event& e) override
	{
		if (e.GetEventType() == Mist::EventType::KeyPressed)
		{
			Mist::KeyPressedEvent& event = (Mist::KeyPressedEvent&)e;
			if (event.GetKeyCode() == MST_KEY_TAB)
				MST_TRACE("Tab key is pressed!! (OnEvent)");
			MST_TRACE("{0}", (char)event.GetKeyCode());
		}
	}

};

class Sandbox : public Mist::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Mist::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Mist::Application* Mist::CreateApplication()
{
	return new Sandbox();
}