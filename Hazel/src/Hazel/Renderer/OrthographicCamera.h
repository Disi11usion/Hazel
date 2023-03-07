//
// Created by 吴棋凡 on 2023/3/7.
//

#pragma once
#include "glm/glm.hpp"
namespace Hazel {

class OrthographicCamera {
public:
  OrthographicCamera(float left, float right, float bottom, float top);
  void SetPosition(const glm::vec3 &position) {
    position_ = position;
    RecalculateViewMatrix();
  }
  void SetRotation(float rotation) {
    rotation_ = rotation;
    RecalculateViewMatrix();
  }
  const glm::vec3 &GetPosition() const { return position_; }
  float GetRotation() const { return rotation_; }
  void RecalculateViewMatrix();
  const glm::mat4 &GetProjectionMatrix() const { return projection_matrix_; }
  const glm::mat4 &GetViewMatrix() const { return view_matrix_; }
  const glm::mat4 &GetViewProjectionMatrix() const { return view_projection_matrix; }

private:
  glm::mat4 projection_matrix_;
  glm::mat4 view_matrix_{};
  glm::mat4 view_projection_matrix{};
  glm::vec3 position_{0.0f, 0.0f, 0.0f};
  float rotation_ = 0.0f;
};

} // namespace Hazel
