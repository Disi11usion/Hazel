//
// Created by 吴棋凡 on 2023/2/22.
//

#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
namespace Hazel {
class Renderer {
public:
  static void BeginScene(OrthographicCamera &camera);
  static void EndScene();
  static void Submit(const std::shared_ptr<Shader> &shader,
                     const std::shared_ptr<VertexArray> &vertexArray);
  inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

public:
  struct SceneData {
    glm::mat4 view_projection_matrix;
  };
  static SceneData *scene_data_;
};
} // namespace Hazel