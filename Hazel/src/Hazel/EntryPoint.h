#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application*  Hazel::CreatApplication();

int main(int argc, char** argv)
{
	printf("hazel engine");
	auto app = Hazel::CreatApplication();
	app->Run();
	delete app;
}

#endif // HZ_PLATFORM_WINDOWS