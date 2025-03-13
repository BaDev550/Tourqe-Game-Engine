#pragma once

#include "TCore.h"

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
