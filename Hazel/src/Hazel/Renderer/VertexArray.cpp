//
// Created by 吴棋凡 on 2023/3/4.
//

#include "VertexArray.h"
#include "Renderer.h"
#include "Plantform/OpenGL/OpenGLVertexArray.h"
namespace Hazel {
VertexArray *VertexArray::Create() {
  switch (Renderer::GetAPI()) {

  case RendererAPI::API::None:
    return nullptr;
  case RendererAPI::API::OpenGL:
    return new OpenGLVertexArray;
  case RendererAPI::API::Vulkan:
    return nullptr;
  }
}
} // namespace Hazel
