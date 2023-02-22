//
// Created by 吴棋凡 on 2023/2/17.
//

#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel {

class OpenGLContext : public GraphicsContext
{
public:
  explicit OpenGLContext(GLFWwindow* windowHandle);

  void Init() override;
  void SwapBuffers() override;
private:
  GLFWwindow* m_WindowHandle;
};

}