//
// Created by 吴棋凡 on 2023/2/22.
//
#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Plantform/OpenGL/OpenGLBuffer.h"
namespace Hazel {
VertexBuffer *Hazel::VertexBuffer::Create(float *vertices, uint32_t size) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::None:
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLVertexBuffer(vertices, size);
  default:
    return nullptr;
  }
}
IndexBuffer *Hazel::IndexBuffer::Create(uint32_t *indices, uint32_t count) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::None:
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLIndexBuffer(indices, count);
  default:
    return nullptr;
  }
}
} // namespace Hazel
