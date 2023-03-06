//
// Created by 吴棋凡 on 2023/3/7.
//
#include "RenderCommand.h"
#include "Plantform/OpenGL/OpenGLRendererAPI.h"
namespace Hazel {
RendererAPI *RenderCommand::s_rendererAPI_ = new OpenGLRendererAPI;
} // namespace Hazel