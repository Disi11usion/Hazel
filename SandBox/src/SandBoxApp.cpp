#include "hzpch.h"
#include "Hazel.h"
class ExampleLayer : public Hazel::Layer {
  using Log [[maybe_unused]] = Hazel::Log;
  using LogClassify [[maybe_unused]] = Hazel::LogClassify;

public:
  explicit ExampleLayer()
      : Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f), camera_position_(0.0f) {
    vertex_array_.reset(Hazel::VertexArray::Create());
    std::array<float, 28> positions = {
        0.5f,  0.5f,  0.0f, 0.8f, 0.2f, 0.8f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 0.5f, 0.5f, 0.5f, 1.0f  // top left
    };
    std::shared_ptr<Hazel::VertexBuffer> vertex_buffer;
    vertex_buffer.reset(Hazel::VertexBuffer::Create(positions));
    vertex_buffer->Bind();
    Hazel::BufferLayout layout = {{Hazel::ShaderDataType::Float3, "a_Position"},
                                  {Hazel::ShaderDataType::FLoat4, "a_Color"}};
    vertex_buffer->SetLayout(layout);
    //@TO DO:
    std::array<unsigned int, 6> indices = {0, 1, 3,  // first Triangle
                                           1, 2, 3}; // second Triangle
    std::shared_ptr<Hazel::IndexBuffer> index_buffer;
    index_buffer.reset(Hazel::IndexBuffer::Create(indices));
    index_buffer->Bind();
    vertex_array_->AddVertexBuffer(vertex_buffer);
    vertex_array_->SetIndexBuffer(index_buffer);

    std::string vertex_src =
        "#version 410 core\n"
        "layout (location = 0) in vec3 a_Position;\n"
        "layout (location = 1) in vec4 a_Color;\n"
        "uniform mat4 u_ViewProjection;\n"
        "out vec4 v_Color;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    gl_Position =u_ViewProjection* vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);\n"
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
    shader_ = std::make_unique<Hazel::Shader>(vertex_src, fragment_src);
  }
  void OnUpdate() override {
    if (Hazel::Input::IsKeyPressed(Hazel::Key::Left)) {
      camera_position_.x += camera_move_speed_;
    } else if (Hazel::Input::IsKeyPressed(Hazel::Key::Right)) {
      camera_position_.x -= camera_move_speed_;
    }
    if (Hazel::Input::IsKeyPressed(Hazel::Key::Up)) {
      camera_position_.y -= camera_move_speed_;
    } else if (Hazel::Input::IsKeyPressed(Hazel::Key::Down)) {
      camera_position_.y += camera_move_speed_;
    }
    if (Hazel::Input::IsKeyPressed(Hazel::Key::A)) {
      camera_rotation_ += camera_rotate_speed_;
    } else if (Hazel::Input::IsKeyPressed(Hazel::Key::D)) {
      camera_rotation_ -= camera_rotate_speed_;
    }
    Hazel::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
    Hazel::RenderCommand::Clear();
    camera_.SetPosition(camera_position_);
    camera_.SetRotation(camera_rotation_);
    Hazel::Renderer::BeginScene(camera_);
    Hazel::Renderer::Submit(shader_, vertex_array_);

    Hazel::Renderer::EndScene();
  }
  void OnEvent(Hazel::Event &event) override {}

private:
  std::shared_ptr<Hazel::VertexArray> vertex_array_;
  std::shared_ptr<Hazel::Shader> shader_;
  Hazel::OrthographicCamera camera_;
  glm::vec3 camera_position_;
  float camera_move_speed_ = 0.1f;
  float camera_rotation_ = 0.0f;
  float camera_rotate_speed_ = 2.0f;
};
class Sandbox : public Hazel::Application {
public:
  Sandbox() { PushLayer(new ExampleLayer()); };
  ~Sandbox() override = default;
};
Hazel::Application *Hazel::CreateApplication() { return new Sandbox(); }