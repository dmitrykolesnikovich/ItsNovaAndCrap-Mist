#pragma once

#include "Log.h"

#ifdef MST_PLATFORM_WINDOWS

extern Mist::Application* Mist::CreateApplication();

int main()
{
	Mist::Log::Init();
	MST_CORE_WARN("Initialized Log!");
	int a = 5;
	MST_INFO("Hello! Var={0}", a);

	auto app = Mist::CreateApplication();
	app->Run();
	delete app;
}

#endif