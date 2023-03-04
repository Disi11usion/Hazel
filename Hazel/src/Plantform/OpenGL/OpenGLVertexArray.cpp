//
// Created by 吴棋凡 on 2023/3/5.
//

#include "OpenGLVertexArray.h"
#include "glad/glad.h"
namespace Hazel {
void OpenGLVertexArray::Bind() const { glBindVertexArray(renderer_id_); }
void OpenGLVertexArray::UnBind() const { glBindVertexArray(0); }
void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer) {
  glBindVertexArray(renderer_id_);
  vertexBuffer->Bind();
  uint32_t index = 0;
  auto &layout = vertexBuffer->GetLayout();
  for (const auto &item : layout) {
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, item.GetElementCount(), ShaderDataTypeToOpenGLBaseType(item.type),
                          item.normalized_ ? GL_TRUE : GL_FALSE, layout.GetStride(),
                          reinterpret_cast<const void *>(item.offset));
    ++index;
  }
  vertex_buffers_.push_back(vertexBuffer);
}
void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer) {
  glBindVertexArray(renderer_id_);
  index_buffer_ = indexBuffer;
  index_buffer_->Bind();
}
void OpenGLVertexArray::SetLayout(const BufferLayout &&layout) {}
OpenGLVertexArray::OpenGLVertexArray() : renderer_id_(0) { glGenVertexArrays(1, &renderer_id_); }
uint32_t OpenGLVertexArray::ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
  switch (type) {

  case ShaderDataType::None:
    return 0;
  case ShaderDataType::Float:
    return GL_FLOAT;
  case ShaderDataType::Float2:
    return GL_FLOAT;
  case ShaderDataType::Float3:
    return GL_FLOAT;
  case ShaderDataType::FLoat4:
    return GL_FLOAT;
  case ShaderDataType::Mat3:
    return GL_FLOAT;
  case ShaderDataType::Mat4:
    return GL_FLOAT;
  case ShaderDataType::Int:
    return GL_INT;
  case ShaderDataType::Int2:
    return GL_INT;
  case ShaderDataType::Int3:
    return GL_INT;
  case ShaderDataType::Int4:
    return GL_INT;
  case ShaderDataType::Bool:
    return GL_INT;
  }
}
} // namespace Hazel
