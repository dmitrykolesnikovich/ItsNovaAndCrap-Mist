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
		MST_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(Mist::Event& e) override
	{
	}

};

class Sandbox : public Mist::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Mist::Application* Mist::CreateApplication()
{
	return new Sandbox();
}