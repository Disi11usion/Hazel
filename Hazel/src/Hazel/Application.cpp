//
// Created by 吴棋凡 on 2023/2/15.
//
#include "glad/glad.h"
#include "Application.h"

#include <memory>
#include "Hazel/Log.h"
namespace Hazel {
Application *Application::s_instance_ = nullptr;

Application::Application() : im_gui_layer_(new ImGuiLayer()) {
  window_ = std::unique_ptr<Window>(Window::Create());
  window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
  Application::s_instance_ = this;
  PushOverLay(im_gui_layer_);
  glGenVertexArrays(1, &current_vao_);
  glBindVertexArray(current_vao_);
  std::array<float, 12> positions = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };
  vertex_buffer_.reset(VertexBuffer::Create(positions));
  vertex_buffer_->Bind();

  std::array<unsigned int, 6> indices = {0, 1, 3,  // first Triangle
                                         1, 2, 3}; // second Triangle
  index_buffer_.reset(IndexBuffer::Create(indices));
  index_buffer_->Bind();


  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  glEnableVertexAttribArray(0);

  std::string vertex_src = "#version 410 core\n"
                           "layout (location = 0) in vec3 aPos;\n"
                           "\n"
                           "void main()\n"
                           "{\n"
                           "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                           "}";
  std::string fragment_src = "#version 410 core\n"
                             "out vec4 FragColor;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                             "} ";
  shader_ = std::make_unique<Shader>(vertex_src, fragment_src);
}

Application::~Application() = default;

void Application::Run() {
  while (running_) {
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    for (auto *const layer : layer_stack_) {
      layer->OnUpdate();
    }
    im_gui_layer_->Begin();
    for (const auto &layer : layer_stack_) {
      layer->OnImGuiRender();
    }
    im_gui_layer_->End();
    window_->OnUpdate();
  }
}
void Application::OnEvent(Event &event) {
  EventDispatcher dispatcher(event);
  dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
  for (auto iterator = layer_stack_.end(); iterator != layer_stack_.begin();) {
    (*--iterator)->OnEvent(event);
    if (event.handled_) {
      break;
    }
  }
}
bool Application::OnWindowClosed(WindowCloseEvent &event) {
  Log::AppLog(Log::LogClassify::INFO, event.ToString());
  running_ = false;
  return true;
}
void Application::PushLayer(Layer *layer) {
  layer_stack_.PushLayer(layer);
  layer->OnAttach();
}
void Application::PushOverLay(Layer *layer) {
  layer_stack_.PushOverlay(layer);
  layer->OnAttach();
}
Window &Application::GetWindow() const { return *window_; }
Application &Application::Get() { return *s_instance_; }
} // namespace Hazel