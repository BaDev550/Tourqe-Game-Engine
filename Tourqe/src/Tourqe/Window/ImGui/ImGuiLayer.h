#pragma once

#include "Tourqe/Window/Layer.h"

#include "Tourqe/Events/KeyEvent.h"
#include "Tourqe/Events/ApplicationEvent.h"
#include "Tourqe/Events/MouseEvent.h"

namespace TourqeE {
	
	class TOURQE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDeatach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
