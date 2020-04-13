#pragma once

#include <utility/LogManager.h>

#ifdef _MSC_VER
#define debugbreak() __debugbreak()
#else
#include <csignal>
#define debugbreak() std::raise(SIGTRAP)
#endif

#define Assert(what, ...)                                                        \
    if (!(what)) {                                                               \
        peach::LogManager::GetInstance().GetLogger("ASSERT").Error(__VA_ARGS__); \
        debugbreak();                                                            \
    }