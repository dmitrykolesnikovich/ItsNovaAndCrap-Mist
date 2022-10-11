#pragma once

#ifdef MST_PLATFORM_WINDOWS

extern Mist::Application* Mist::CreateApplication();

int main()
{
	auto app = Mist::CreateApplication();
	app->Run();
	delete app;
}

#endif