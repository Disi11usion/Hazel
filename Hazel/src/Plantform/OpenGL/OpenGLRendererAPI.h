//
// Created by 吴棋凡 on 2023/3/7.
//

#pragma once
#include "Hazel/Renderer/RendererAPI.h"
namespace Hazel {

class OpenGLRendererAPI: public RendererAPI{
public:
  ~OpenGLRendererAPI() override = default;
  void Clear() override;
  void SetClearColor(const glm::vec4 &color) override;
  void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) override;
};

} // namespace Hazel
