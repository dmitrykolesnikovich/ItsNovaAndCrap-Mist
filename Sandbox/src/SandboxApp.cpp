#include <Mist.h>

class Sandbox : public Mist::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Mist::Application* Mist::CreateApplication()
{
	return new Sandbox();
}