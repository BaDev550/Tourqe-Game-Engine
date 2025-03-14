#include "tupch.h"
#include "Application.h"

namespace TourqeE {
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(800, 800);
		TU_TRACE(e.ToString());

		while (true) {

		}
	}
}