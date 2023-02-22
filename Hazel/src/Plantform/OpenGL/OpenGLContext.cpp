//
// Created by 吴棋凡 on 2023/2/17.
//

#include "OpenGLContext.h"
#include "Hazel/Log.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hazel {

OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {}

void OpenGLContext::Init() {

  glfwMakeContextCurrent(m_WindowHandle);
  int const status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
  if (status == 0) {
    Hazel::Log::CoreLog(Hazel::LogClassify::WARN, "Failed to initialize Glad!");
  }

  Hazel::Log::CoreLog(Hazel::LogClassify::INFO, "OpenGL Info:");
  Hazel::Log::CoreLog(Hazel::LogClassify::INFO, "Vendor: {0}", *glGetString(GL_VENDOR));
  Hazel::Log::CoreLog(Hazel::LogClassify::INFO, "Renderer: {0}", *glGetString(GL_RENDERER));
  Hazel::Log::CoreLog(Hazel::LogClassify::INFO, "Version: {0}", *glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() { glfwSwapBuffers(m_WindowHandle); }

} // namespace Hazel