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
		if (event.GetEventType() == TourqeE::EventType::KeyPressed) {
			TourqeE::KeyPressedEvent& e = (TourqeE::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TU_KEY_TAB)
				TU_INFO("Tab key pressed");

			TU_TRACE("{0}", (char)e.GetKeyCode());
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