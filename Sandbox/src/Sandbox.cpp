#include <TourqeEngine.h>
#include "imgui/imgui.h"

class ExampleLayer : public TourqeE::Layer {
public:
	ExampleLayer() 
		: Layer("Test"){
	}

	void OnUpdate() override {

	}

	virtual void OnImGuiRender() override {
		if (ImGui::Begin("Log Sender")) {
			if (ImGui::Button("Send Info")) {
				TU_INFO("TEST Log");
			}
			if (ImGui::Button("Send Error")) {
				TU_ERROR("TEST Log");
			}
			ImGui::End();
		}
	}

	void OnEvent(TourqeE::Event& event) override {
		if (event.GetEventType() == TourqeE::EventType::KeyPressed || event.GetEventType() == TourqeE::EventType::MouseButtonPressed) {
			TourqeE::KeyPressedEvent& e = (TourqeE::KeyPressedEvent&)event;
			TourqeE::MouseButtonPressedEvent& mE = (TourqeE::MouseButtonPressedEvent&)event;
			
			if(e.GetEventType() == TourqeE::EventType::KeyPressed)
				TU_TRACE("{0}", (char)e.GetKeyCode());
			if (mE.GetEventType() == TourqeE::EventType::MouseButtonPressed)
				TU_TRACE("Mouse Button: {0}", mE.GetMouseButton());
		}
	}
};

class Sandbox : public TourqeE::Application {
public:
	Sandbox(){
		PushLayer(new ExampleLayer());
	}
	~Sandbox(){}
};

TourqeE::Application* TourqeE::CreateApplication() {
	return new Sandbox();
}