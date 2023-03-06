//
// Created by 吴棋凡 on 2023/2/22.
//
#include "hzpch.h"
#include "Renderer.h"
namespace Hazel {
void Renderer::BeginScene() {
}
void Renderer::EndScene() {}
void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray) {
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}
} // namespace Hazel