//
// Created by 吴棋凡 on 2023/3/6.
//

#pragma once
#include "glm/glm.hpp"
#include "VertexArray.h"
namespace Hazel {
class RendererAPI {
public:
  virtual ~RendererAPI() = default;
  enum class API { None = 0, OpenGL = 1, Vulkan = 2 };
  virtual void Clear() = 0;
  virtual void SetClearColor(const glm::vec4 &color) = 0;
  virtual void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) = 0;
  inline static API GetAPI() { return s_API; }

private:
  static API s_API;
};
} // namespace Hazel
