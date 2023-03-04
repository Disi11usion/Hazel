//
// Created by 吴棋凡 on 2023/3/5.
//

#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "vector"
namespace Hazel {

class OpenGLVertexArray : public VertexArray {
public:
  ~OpenGLVertexArray() override = default;
  void Bind() const override;
  void UnBind() const override;
  void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)  override;
  void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)  override;
  void SetLayout(const BufferLayout &&layout) override;
  OpenGLVertexArray();
  static uint32_t ShaderDataTypeToOpenGLBaseType(ShaderDataType type);
private:
  std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
  std::shared_ptr<IndexBuffer> index_buffer_;
  uint32_t renderer_id_;
};

} // namespace Hazel
