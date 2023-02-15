//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
int main() {
  Hazel::Log::Init();
  Hazel::Log::CoreLog(Hazel::Log::LogClassify::WARN, "Initialized log!");
  std::unique_ptr<Hazel::Application> app(Hazel::CreateApplication());
  app->Run();
  return 0;
}
