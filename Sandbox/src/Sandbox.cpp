#include <TourqeEngine.h>

class Sandbox : public TourqeE::Application {
public:
	Sandbox(){}
	~Sandbox(){}
};

TourqeE::Application* TourqeE::CreateApplication() {
	return new Sandbox();
}