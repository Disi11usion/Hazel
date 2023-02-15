//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"
namespace Hazel {
class Application {
 public:
  Application();
  virtual ~Application();
  void Run();
  void OnEvent(Event & event);

 private:
  std::unique_ptr<Window> window_;
  bool running_= true;
  bool OnWindowClosed(WindowCloseEvent& event);
};
Application* CreateApplication();
}  // namespace Hazel