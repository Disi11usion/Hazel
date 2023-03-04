//
// Created by 吴棋凡 on 2023/2/22.
//

#pragma once
#include "Hazel/Renderer/Buffer.h"
namespace Hazel {
class OpenGLVertexBuffer : public VertexBuffer {
public:
  OpenGLVertexBuffer(float *vertices, uint32_t size);
  ~OpenGLVertexBuffer() override;
  void Bind() const override;
  void UnBind() const override;
  BufferLayout& GetLayout() override;
  void SetLayout(BufferLayout &layout) override;

private:
  uint32_t renderID_{0};
  BufferLayout layout_{};
};
class OpenGLIndexBuffer : public IndexBuffer {
public:
  OpenGLIndexBuffer(uint32_t *vertices, uint32_t count);
  ~OpenGLIndexBuffer() override;
  void Bind() const override;
  void UnBind() const override;
  uint32_t GetCount() const override;

private:
  uint32_t renderID_{0};
  uint32_t count;
};
} // namespace Hazel