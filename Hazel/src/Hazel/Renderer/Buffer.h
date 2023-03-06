//
// Created by 吴棋凡 on 2023/2/22.
//

#pragma once
#include "vector"
#include "string"
namespace Hazel {
enum class ShaderDataType {
  None = 0,
  Float,
  Float2,
  Float3,
  FLoat4,
  Mat3,
  Mat4,
  Int,
  Int2,
  Int3,
  Int4,
  Bool
};
class BufferLayout {
public:
  struct BufferElement {
    std::string name;
    uint32_t offset{0};
    uint32_t count{0};
    uint32_t size{0};
    bool normalized_;
    ShaderDataType type;
    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
      switch (type) {
      case ShaderDataType::Float:
        return 4;
      case ShaderDataType::None:
        return 0;
      case ShaderDataType::Float2:
        return 8;
      case ShaderDataType::Float3:
        return 12;
      case ShaderDataType::FLoat4:
        return 16;
      case ShaderDataType::Mat3:
        return 4 * 3 * 3;
      case ShaderDataType::Mat4:
        return 4 * 4 * 4;
      case ShaderDataType::Int:
        return 4;
      case ShaderDataType::Int2:
        return 8;
      case ShaderDataType::Int3:
        return 12;
      case ShaderDataType::Int4:
        return 16;
      case ShaderDataType::Bool:
        return 1;
      default:
        return 0;
      }
    }
    BufferElement(ShaderDataType type, const std::string &&name, bool normalized = false)
        : name(name), size(ShaderDataTypeSize(type)), type(type), normalized_(normalized){};
    uint32_t GetElementCount() const {
      switch (type) {
      case ShaderDataType::None:
        break;
      case ShaderDataType::Float:
        break;
      case ShaderDataType::Float2:
        return 2;
      case ShaderDataType::Float3:
        return 3;
      case ShaderDataType::FLoat4:
        return 4;
      case ShaderDataType::Mat3:
        return 3;
      case ShaderDataType::Mat4:
        return 4;
      case ShaderDataType::Int:
        return 1;
      case ShaderDataType::Int2:
        return 2;
      case ShaderDataType::Int3:
        return 3;
      case ShaderDataType::Int4:
        return 4;
      case ShaderDataType::Bool:
        return 1;
      }
      return 0;
    }
  };
  const std::vector<BufferElement> &GetElements() const { return elements_; }
  BufferLayout(const std::initializer_list<BufferElement> &element) : elements_(element) {
    CalculateOffsetAndStride();
  }
  std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
  std::vector<BufferElement>::iterator end() { return elements_.end(); }
  uint32_t GetStride() const { return stride_; }
  uint32_t GetLayoutSize()const{return elements_.size();}
private:
  std::vector<BufferElement> elements_;
  uint32_t stride_{0};
  void CalculateOffsetAndStride() {
    uint32_t offset = 0;
    stride_ = 0;
    for (auto &element : elements_) {
      element.offset = offset;
      offset += element.size;
      stride_ += element.size;
    }
  }
};
class VertexBuffer {
public:
  virtual ~VertexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
  static VertexBuffer *Create(float *vertices, uint32_t size);
  template <size_t size> static VertexBuffer *Create(std::array<float, size> &vertices) {
    return VertexBuffer::Create(vertices.begin(), sizeof(vertices));
  }
  virtual BufferLayout &GetLayout() = 0;
  virtual void SetLayout(BufferLayout &layout) = 0;
};
class IndexBuffer {
public:
  virtual ~IndexBuffer() = default;
  virtual void Bind() const = 0;
  virtual void UnBind() const = 0;
  static IndexBuffer *Create(uint32_t *indices, uint32_t count);
  template <size_t count> static IndexBuffer *Create(std::array<uint32_t, count> &indices) {
    return IndexBuffer::Create(indices.begin(), count);
  }
  virtual uint32_t GetCount() const = 0;
};
} // namespace Hazel