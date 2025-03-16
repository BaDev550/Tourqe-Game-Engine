#pragma once

#include "tupch.h"
#include "Tourqe/TCore.h"
#include "Tourqe/Events/Event.h"

typedef unsigned int uint;
namespace TourqeE {
	struct WindowPropeties
	{
		std::string Title;
		uint Width;
		uint Height;

		WindowPropeties(const std::string& title = "Tourqe Game Engine", uint width = 1280, uint height = 720) :
			Title(title), Width(width), Height(height) {}
	};
	class TOURQE_API Window
	{
	public:
		using EventCallbackFuntion = std::function<void(Event&)>;
		virtual ~Window() {}
		virtual void OnUpdate() = 0;
		virtual uint GetWidth() const = 0;
		virtual uint GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFuntion& callback) = 0;
		virtual void SetVsync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowPropeties& props = WindowPropeties());
	};
}
