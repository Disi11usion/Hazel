//
// Created by 吴棋凡 on 2023/2/16.
//

#pragma once
#include "Hazel/Core/Layer.h"
namespace Hazel {
class ImGuiLayer: public Layer{
public:
  ImGuiLayer();
  ~ImGuiLayer() override;
  void OnUpdate() override;
  void OnEvent(Event &event) override;
  void OnAttach() override;
  void OnDetach() override;
  static void SetDarkThemeColors();
private:
  float time_=0.0f;
};

} // namespace Hazel
