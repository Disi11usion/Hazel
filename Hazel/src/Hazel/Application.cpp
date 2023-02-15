//
// Created by 吴棋凡 on 2023/2/15.
//
#include "Application.h"
#include "Hazel/Log.h"
#include "glad/glad.h"
namespace Hazel {
Application::Application() {
  window_ = std::unique_ptr<Window>(Window::Create());
  window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
}

Application::~Application() = default;

void Application::Run() {
  while (running_) {
    glClearColor(1, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    window_->OnUpdate();
  }
}
void Application::OnEvent(Event& event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
}
bool Application::OnWindowClosed(WindowCloseEvent& event) {
  Log::AppLog(Log::LogClassify::INFO, event.ToString());
  running_ = false;
  return true;
}
}  // namespace Hazel