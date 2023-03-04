//
// Created by 吴棋凡 on 2023/2/16.
//
#include <glad/glad.h>
#include "MacOsWindow.h"
#include "Hazel/Core/Log.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"
#include "Plantform/OpenGL/OpenGLContext.h"
namespace Hazel {
static void GlfwErrorCallback(int error, const char *description) {
  Log::CoreLog(Log::LogClassify::ERROR, "GLFW Error {0}: {1}", error, description);
}
static bool s_GLFW_Initialized = false;

MacOsWindow::MacOsWindow(const WindowProps &props) : window_{nullptr} { Init(props); }

MacOsWindow::~MacOsWindow() { Shutdown(); }

void MacOsWindow::Init(const WindowProps &props) {
  window_data_.title = props.title;
  window_data_.width = props.width;
  window_data_.height = props.height;
  Hazel::Log::CoreLog(Log::LogClassify::INFO, "Creating window {0} ({1}, {2})", props.title, props.width, props.height);
  if (!s_GLFW_Initialized) {
    const int K_Success = glfwInit();
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwSetErrorCallback(([](int ErrorCode, const char *description) {
      Log::CoreLog(Log::LogClassify::WARN, "glfw Error {0}: {1}", ErrorCode, description);
    }));
    if (K_Success == 0) {
      Hazel::Log::CoreLog(Log::LogClassify::WARN, "Could not intialize GLFW!");
    } else {
      s_GLFW_Initialized = true;
    }
  }
  window_ = glfwCreateWindow(static_cast<int>(props.width), static_cast<int>(props.height), window_data_.title.c_str(),
                             nullptr, nullptr);
  // gladload
  graphics_context_ = new OpenGLContext(window_);
  graphics_context_->Init();

  glfwSetWindowUserPointer(window_, &window_data_);
  SetVSync(true);
  // glfw callback
  glfwSetWindowSizeCallback(window_, [](GLFWwindow *window, int width, int height) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    WindowResizeEvent event(width, height);
    window_data.event_callback(event);
    window_data.width = width;
    window_data.height = height;
  });
  glfwSetWindowCloseCallback(window_, [](GLFWwindow *window) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    WindowCloseEvent event;
    window_data.event_callback(event);
  });
  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int, int action, int) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    switch (action) {
    case GLFW_PRESS: {
      KeyPressedEvent event(key, false);
      window_data.event_callback(event);
      break;
    }
    case GLFW_RELEASE: {
      KeyReleasedEvent event(key);
      window_data.event_callback(event);
      break;
    }
    case GLFW_REPEAT: {
      KeyPressedEvent event(key, true);
      window_data.event_callback(event);
      break;
    }
    default:
      break;
    }
  });
  glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    switch (action) {
    case GLFW_PRESS: {
      MouseButtonPressedEvent event(button);
      window_data.event_callback(event);
      break;
    }
    case GLFW_RELEASE: {
      MouseButtonReleasedEvent event(button);
      window_data.event_callback(event);
      break;
    }
    default:
      break;
    }
  });
  glfwSetScrollCallback(window_, [](GLFWwindow *window, double x_offset, double y_offset) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    MouseScrolledEvent event(static_cast<float>(x_offset), static_cast<float>(y_offset));
    window_data.event_callback(event);
  });
  glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x_position, double y_position) {
    auto &window_data = *(static_cast<WindowData *>(glfwGetWindowUserPointer(window)));
    MouseMovedEvent event(static_cast<float>(x_position), static_cast<float>(y_position));
    window_data.event_callback(event);
  });
}
void MacOsWindow::Shutdown() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}
void MacOsWindow::OnUpdate() {
  if (graphics_context_ != nullptr) {
    graphics_context_->SwapBuffers();
  }
  glfwPollEvents();
}
void MacOsWindow::SetVSync(bool enabled) {
  if (enabled) {
    glfwSwapInterval(1);
  } else {
    glfwSwapInterval(0);
  }
  window_data_.v_sync = enabled;
}
bool MacOsWindow::IsVSync() const { return window_data_.v_sync; }
} // namespace Hazel