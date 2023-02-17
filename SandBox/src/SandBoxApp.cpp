#include "hzpch.h"
#include "Hazel.h"
class ExampleLayer : public Hazel::Layer {
  using Log = Hazel::Log;
  using LogClassify = Hazel::LogClassify;

public:
  explicit ExampleLayer() : Layer("Example") {}
  void OnUpdate() override {
  }
  void OnEvent(Hazel::Event &event) override {}
};
class Sandbox : public Hazel::Application {
public:
  Sandbox() {
    PushLayer(new ExampleLayer());
    PushLayer(new Hazel::ImGuiLayer());
  };
  ~Sandbox() override = default;
};
Hazel::Application *Hazel::CreateApplication() { return new Sandbox(); }