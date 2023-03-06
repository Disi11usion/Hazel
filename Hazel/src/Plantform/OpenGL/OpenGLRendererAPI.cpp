//
// Created by 吴棋凡 on 2023/3/7.
//
#include "glad/glad.h"
#include "OpenGLRendererAPI.h"

namespace Hazel {
void OpenGLRendererAPI::Clear() {
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) {
  glClearColor(color.x, color.g, color.b, color.a);
}
void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray> &vertexArray) {
  glDrawElements(GL_TRIANGLES,vertexArray->GetIndexBuffer()->GetCount(),GL_UNSIGNED_INT, nullptr);
}
} // namespace Hazel
