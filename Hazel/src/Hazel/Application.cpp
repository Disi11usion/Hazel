//
// Created by 吴棋凡 on 2023/2/15.
//
#include "hzpch.h"
#include "Application.h"
#include "Hazel/Core/Log.h"
namespace Hazel {
Application *Application::s_instance_ = nullptr;

Application::Application() : im_gui_layer_(new ImGuiLayer()){
  window_ = std::unique_ptr<Window>(Window::Create());
  window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
  Application::s_instance_ = this;
  PushOverLay(im_gui_layer_);

}

Application::~Application() = default;

void Application::Run() {
  while (running_) {

    for (auto *const layer : layer_stack_) {
      layer->OnUpdate();
    }
    im_gui_layer_->Begin();
    for (const auto &layer : layer_stack_) {
      layer->OnImGuiRender();
    }
    im_gui_layer_->End();
    window_->OnUpdate();
  }
}
void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(
      std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
  for (auto iterator = layer_stack_.end(); iterator != layer_stack_.begin();) {
    (*--iterator)->OnEvent(event);
    if (event.handled_) {
      break;
    }
  }
}
bool Application::OnWindowClosed(WindowCloseEvent &event) {
  Log::AppLog(Log::LogClassify::INFO, event.ToString());
  running_ = false;
  return true;
}
void Application::PushLayer(Layer *layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}
void Application::PushOverLay(Layer *layer) {
  layer_stack_.PushOverlay(layer);
  layer->OnAttach();
}
Window &Application::GetWindow() const { return *window_; }
Application &Application::Get() { return *s_instance_; }
} // namespace Hazel