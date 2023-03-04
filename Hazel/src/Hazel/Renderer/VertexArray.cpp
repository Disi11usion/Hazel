//
// Created by 吴棋凡 on 2023/3/4.
//

#include "VertexArray.h"
#include "Renderer.h"
#include "Plantform/OpenGL/OpenGLVertexArray.h"
namespace Hazel {
VertexArray *VertexArray::Create() {
  switch (Renderer::GetAPI()) {

  case RendererAPI::None:
    return nullptr;
  case RendererAPI::OpenGL:
    return new OpenGLVertexArray;
  case RendererAPI::Vulkan:
    return nullptr;
  }
}
} // namespace Hazel
