//
// Created by 吴棋凡 on 2023/2/15.
//
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
namespace Hazel {
std::shared_ptr<spdlog::logger> Log::core_logger_s_;
std::shared_ptr<spdlog::logger> Log::client_logger_s_;
void Log::Init() {
  spdlog::set_pattern("%^[%T] %n: %v%$");
  core_logger_s_ = spdlog::stdout_color_mt("HAZEL");
  core_logger_s_->set_level(spdlog::level::trace);
  client_logger_s_ = spdlog::stdout_color_mt("APP");
  client_logger_s_->set_level(spdlog::level::trace);
}
}  // namespace Hazel