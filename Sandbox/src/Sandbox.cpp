#include <TourqeEngine.h>

class ExampleLayer : public TourqeE::Layer {
public:
	ExampleLayer() 
		: Layer("Test"){}

	void OnUpdate() override {

	}

	void OnEvent(TourqeE::Event& event) override {

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