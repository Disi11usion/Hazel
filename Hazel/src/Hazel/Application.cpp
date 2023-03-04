//
// Created by 吴棋凡 on 2023/2/15.
//
#include "hzpch.h"
#include "glad/glad.h"
#include "Application.h"
#include "Hazel/Core/Log.h"
namespace Hazel {
Application *Application::s_instance_ = nullptr;

Application::Application() : im_gui_layer_(new ImGuiLayer()) {
  window_ = std::unique_ptr<Window>(Window::Create());
  window_->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
  Application::s_instance_ = this;
  PushOverLay(im_gui_layer_);
  vertex_array_.reset(VertexArray::Create());
  std::array<float, 28> positions = {
      0.5f,  0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // top right
      0.5f,  -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f, // bottom right
      -0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, // bottom left
      -0.5f, 0.5f,  0.0f, 0.5f, 0.5f, 0.5f, 1.0f  // top left
  };
  vertex_buffer_.reset(VertexBuffer::Create(positions));
  vertex_buffer_->Bind();
  BufferLayout layout = {{ShaderDataType::Float3, "a_Position"},
                         {ShaderDataType::FLoat4, "a_Color"}};
  //@TO DO:
  vertex_buffer_->SetLayout(layout);
  std::array<unsigned int, 6> indices = {0, 1, 3,  // first Triangle
                                         1, 2, 3}; // second Triangle
  index_buffer_.reset(IndexBuffer::Create(indices));
  index_buffer_->Bind();
  vertex_array_->AddVertexBuffer(vertex_buffer_);
  vertex_array_->SetIndexBuffer(index_buffer_);
  std::string vertex_src =
      "#version 410 core\n"
      "layout (location = 0) in vec3 a_Position;\n"
      "layout (location = 1) in vec4 a_Color;\n"
      "out vec4 v_Color;\n"
      "\n"
      "void main()\n"
      "{\n"
      "    gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);\n"
      "v_Color=a_Color;\n"
      "}";
  std::string fragment_src = "#version 410 core\n"
                             "layout (location = 0) out vec4 FragColor;\n"
                             "in vec4 v_Color;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "    FragColor = v_Color;\n"
                             "} ";
  shader_ = std::make_unique<Shader>(vertex_src, fragment_src);
}

Application::~Application() = default;

void Application::Run() {
  while (running_) {
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    shader_->Bind();
    vertex_array_->Bind();
    glDrawElements(GL_TRIANGLES, index_buffer_->GetCount(), GL_UNSIGNED_INT, nullptr);
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
  dispatcher.Dispatch<WindowCloseEvent>(
      std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
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