#pragma once

#include "Tourqe/TCore.h"
#include "Tourqe/Events/Event.h"

namespace TourqeE {
	class TOURQE_API Layer
	{
	public:
		Layer(const std::string& name = "Example_Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDeatach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}