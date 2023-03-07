//
// Created by 吴棋凡 on 2023/2/22.
//
#include "hzpch.h"
#include "Renderer.h"
namespace Hazel {
Renderer::SceneData *Renderer::scene_data_ = new Renderer::SceneData;
void Renderer::BeginScene(OrthographicCamera &camera) {
  scene_data_->view_projection_matrix = camera.GetViewProjectionMatrix();
}
void Renderer::EndScene() {}
void Renderer::Submit(const std::shared_ptr<Shader> &shader,
                      const std::shared_ptr<VertexArray> &vertexArray) {
  shader->Bind();
  shader->UploadUniformMat4("u_ViewProjection", scene_data_->view_projection_matrix);
  vertexArray->Bind();
  RenderCommand::DrawIndexed(vertexArray);
}
} // namespace Hazel