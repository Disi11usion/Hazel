//
// Created by 吴棋凡 on 2023/2/22.
//

#pragma once
namespace Hazel {
enum class RendererAPI { None = 0, OpenGL = 1, Vulkan = 2 };
class Renderer {
private:
  static RendererAPI renderer_api_;

public:
  static RendererAPI GetAPI() { return renderer_api_; }
};
} // namespace Hazel