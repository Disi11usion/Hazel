//
// Created by 吴棋凡 on 2023/2/22.
//

#pragma once
namespace Hazel {
class VertexBuffer {
public:
  virtual ~VertexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
  static VertexBuffer *Create(float *vertices, uint32_t size);
  template <size_t size> static VertexBuffer *Create(std::array<float, size> &vertices) {
    return VertexBuffer::Create(vertices.begin(), sizeof(vertices));
  }
};
class IndexBuffer {
public:
  virtual ~IndexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
  static IndexBuffer *Create(uint32_t *indices, uint32_t count);
  template <size_t count> static IndexBuffer *Create(std::array<uint32_t , count> &indices) {
    return IndexBuffer::Create(indices.begin(), count);
  }
};
} // namespace Hazel