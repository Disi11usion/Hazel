//
// Created by 吴棋凡 on 2023/3/7.
//

#pragma once
#include "RendererAPI.h"
namespace Hazel {
class RenderCommand {
public:
  inline static void DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
    s_rendererAPI_->DrawIndexed(vertexArray);
  }
  inline static void Clear() { s_rendererAPI_->Clear(); }
  inline static void SetClearColor(const glm::vec4 &color) { s_rendererAPI_->SetClearColor(color); }

private:
  static RendererAPI *s_rendererAPI_;
};
} // namespace Hazel