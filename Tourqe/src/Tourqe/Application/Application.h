#pragma once

#include "Tourqe/TCore.h"
#include "Tourqe/Application/Logger.h"
#include "Tourqe/Events/ApplicationEvent.h"

namespace TourqeE {

	class TOURQE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}
