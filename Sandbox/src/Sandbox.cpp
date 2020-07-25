#pragma once

#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox() {};
	~Sandbox() {};
};

Hazel::Application* Hazel::CreateApplication()
{
	HZ_INFO("Hello");
	return new Sandbox();
}