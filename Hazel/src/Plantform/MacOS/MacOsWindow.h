//
// Created by 吴棋凡 on 2023/2/16.
//

#pragma once
#include <GLFW/glfw3.h>

#include "Hazel/Window.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Renderer/GraphicsContext.h"

namespace Hazel {

class MacOsWindow : public Window {
 public:
  explicit MacOsWindow(const WindowProps& props);
  ~MacOsWindow() override;

  void OnUpdate() override;

  unsigned int GetWidth() const override { return window_data_.width; }
  unsigned int GetHeight() const override { return window_data_.height; }

  // Window attributes
  void SetEventCallback(const EventCallbackFn& callback) override { window_data_.event_callback = callback; }
  void SetVSync(bool enabled) override;
  bool IsVSync() const override;

  void* GetNativeWindow() const override { return window_; }

 private:
  void Init(const WindowProps& props);
  void Shutdown();

  GLFWwindow* window_;
  GraphicsContext* graphics_context_{};
  struct WindowData {
    std::string title;
    unsigned int width, height;
    bool v_sync;
    EventCallbackFn event_callback;
  };

  WindowData window_data_;
};
Window* Window::Create(const WindowProps& props) { return new MacOsWindow(props); }
}  // namespace Hazel