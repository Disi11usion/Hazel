//
// Created by 吴棋凡 on 2023/2/22.
//
#include "hzpch.h"
#include "glad/glad.h"
#include "OpenGLBuffer.h"
Hazel::OpenGLVertexBuffer::OpenGLVertexBuffer(float *vertices, uint32_t size) {
  glGenBuffers(1, &renderID_);
  glBindBuffer(GL_ARRAY_BUFFER, renderID_);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
void Hazel::OpenGLVertexBuffer::Bind() const { glBindBuffer(GL_ARRAY_BUFFER, renderID_); }
void Hazel::OpenGLVertexBuffer::UnBind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
Hazel::OpenGLVertexBuffer::~OpenGLVertexBuffer() { glDeleteBuffers(1, &renderID_); }
Hazel::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count) {
  glGenBuffers(1, &renderID_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}
Hazel::OpenGLIndexBuffer::~OpenGLIndexBuffer() { glDeleteBuffers(1, &renderID_); }
void Hazel::OpenGLIndexBuffer::Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID_); }
void Hazel::OpenGLIndexBuffer::UnBind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
