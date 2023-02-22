//
// Created by 吴棋凡 on 2023/2/17.
//

#pragma once
#include <string>
#include <cstdint>
namespace Hazel {

class Shader {
public:
  Shader(const std::string &vertex_src, const std::string &fragment_src);
  ~Shader();
  void Bind() const;
  void UnBind() const;

private:
  uint32_t rendererID_;
};

} // namespace Hazel
