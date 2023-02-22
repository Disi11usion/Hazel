//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
#include <hzpch.h>
#ifdef HZ_PLATFORM_MACOS
#ifdef HZ_BUILD_DLL
#endif
#endif
#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x
#define BIT(x) (1 << x)
#define HZ_BIND_EVENT_FN(fn)                                                                                           \
  [this](auto &&...args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
namespace Hazel {
template <typename T> using Scope = std::unique_ptr<T>;
template <typename T, typename... Args> constexpr Scope<T> CreateScope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T> using Ref = std::shared_ptr<T>;
template <typename T, typename... Args> constexpr Ref<T> CreateRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

} // namespace Hazel