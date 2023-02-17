//
// Created by 吴棋凡 on 2023/2/16.
//

#pragma once

#include "Hazel/Core/Timestep.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

class Layer {
public:
  explicit Layer(const std::string &&name = "Layer");
  virtual ~Layer() = default;

  virtual void OnAttach() {}
  virtual void OnDetach() {}
  virtual void OnUpdate() {}
  virtual void OnUpdate(Timestep timestep) {}
  virtual void OnImGuiRender() {}
  virtual void OnEvent(Event &event) {}

  const std::string &GetName() const { return debug_name_; }

protected:
  std::string debug_name_;
};

} // namespace Hazel
