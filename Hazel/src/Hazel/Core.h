//
// Created by 吴棋凡 on 2023/2/15.
//

#pragma once
#ifdef  HZ_PLATFORM_MACOS
#ifdef HZ_BUILD_DLL
#endif
#endif
#define HZ_EXPAND_MACRO(x) x
#define HZ_STRINGIFY_MACRO(x) #x
#define BIT(x) (1<<x)
#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
