#pragma once

#ifdef TU_PLATFORM_WINDOWS

extern TourqeE::Application* TourqeE::CreateApplication();

int main(int argc, char** argv) {
	TourqeE::Logger::Init();
	TU_ENGINE_WARN("Logger Started");
	TU_INFO("Application Started");
	
	auto app = TourqeE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // TU_PLATFORM_WINDOWS

