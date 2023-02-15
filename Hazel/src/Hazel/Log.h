//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
#include "fmt/core.h"
#include "spdlog/spdlog.h"
namespace Hazel {
template <class FormatString>
concept runtime_fmtable = requires(FormatString format_string) { fmt::runtime(format_string); };
class Log {
 public:
  static void Init();
  enum class LogClassify { INFO, WARN, ERROR, TRACE };
  template <runtime_fmtable T, typename... Args>
  static void CoreLog(LogClassify classify, T format_string, Args &&...args) {
    const auto K_Msg = fmt::format(fmt::runtime(format_string), args...);
    switch (classify) {
      case LogClassify::INFO:
        core_logger_s_->info(K_Msg);
        break;
      case LogClassify::ERROR:
        core_logger_s_->error(K_Msg);
      case LogClassify::WARN:
        core_logger_s_->warn(K_Msg);
        break;
      case LogClassify::TRACE:
        core_logger_s_->trace(K_Msg);
        break;
    }
  };
  template <runtime_fmtable T, typename... Args>
  static void AppLog(LogClassify classify, T format_string, Args &&...args) {
    const auto K_Msg = fmt::format(fmt::runtime(format_string), args...);
    switch (classify) {
      case LogClassify::INFO:
        client_logger_s_->info(K_Msg);
        break;
      case LogClassify::ERROR:
        client_logger_s_->error(K_Msg);
      case LogClassify::WARN:
        client_logger_s_->warn(K_Msg);
        break;
      case LogClassify::TRACE:
        client_logger_s_->trace(K_Msg);
        break;
    }
  };

 private:
  static const std::shared_ptr<spdlog::logger> &GetCoreLogger() { return core_logger_s_; }
  static const std::shared_ptr<spdlog::logger> &GetClientLogger() { return client_logger_s_; }
  static std::shared_ptr<spdlog::logger> core_logger_s_;
  static std::shared_ptr<spdlog::logger> client_logger_s_;
};

using LogClassify = Log::LogClassify;
}  // namespace Hazel