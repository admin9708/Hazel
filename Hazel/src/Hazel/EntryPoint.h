#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application*  Hazel::CreatApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();

	HZ_CORE_WARN("Initialized Log");
	int a = 5;
	HZ_INFO("var = {0}", a);


	auto app = Hazel::CreatApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS