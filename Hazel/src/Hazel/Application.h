//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Hazel/Core/LayerStack.h"
#include "Hazel/Gui/ImGuiLayer.h"
//templory
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/Shader.h"
namespace Hazel {
class Application {
 public:
  Application();
  virtual ~Application();
  void Run();
  void OnEvent(Event & ph_1);
  void PushLayer(Layer* layer);
  void PushOverLay(Layer* layer);
   Window &GetWindow() const;
  static Application& Get();
  static Application* s_instance_;
private:
  ImGuiLayer* im_gui_layer_;
  std::unique_ptr<Window> window_;
  LayerStack layer_stack_;
  bool running_= true;
  bool OnWindowClosed(WindowCloseEvent& event);
  unsigned int current_vao_=0;
  std::unique_ptr<IndexBuffer> index_buffer_;
  std::unique_ptr<VertexBuffer> vertex_buffer_;
  std::unique_ptr<Shader> shader_;
};
Application* CreateApplication();
}  // namespace Hazel