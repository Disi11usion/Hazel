#include "hzpch.h"
#include "Hazel.h"
class ExampleLayer : public Hazel::Layer {
  using Log [[maybe_unused]] = Hazel::Log;
  using LogClassify [[maybe_unused]] = Hazel::LogClassify;

public:
  explicit ExampleLayer() : Layer("Example") {}
  void OnUpdate() override {
  }
  void OnEvent(Hazel::Event &event) override {

  }
};
class Sandbox : public Hazel::Application {
public:
  Sandbox() {
    PushLayer(new ExampleLayer());
  };
  ~Sandbox() override = default;
};
Hazel::Application *Hazel::CreateApplication() { return new Sandbox(); }