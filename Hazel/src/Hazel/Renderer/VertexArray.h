//
// Created by 吴棋凡 on 2023/3/4.
//

#pragma once

#include "memory"
#include "Buffer.h"
namespace Hazel {

class VertexArray {
public:
  virtual ~VertexArray() = default;
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
  virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)  = 0;
  virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)  = 0;
  virtual void SetLayout(const BufferLayout &&layout) = 0;
  static VertexArray *Create();
};

} // namespace Hazel
