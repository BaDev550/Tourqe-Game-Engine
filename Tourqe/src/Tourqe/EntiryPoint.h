#pragma once

#ifdef TU_PLATFORM_WINDOWS

extern TourqeE::Application* TourqeE::CreateApplication();

int main(int argc, char** argv) {
	auto app = TourqeE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif // TU_PLATFORM_WINDOWS

