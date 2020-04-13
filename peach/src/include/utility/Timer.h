#pragma once

#include <utility/TimeSpan.h>

#include <chrono>

namespace peach {

class Timer {
public:
    Timer();

    TimeSpan Tick();
    TimeSpan Total();

    void Reset();

private:
    std::chrono::high_resolution_clock::time_point mCreationTime;
    std::chrono::high_resolution_clock::time_point mLastTick;
};

} // namespace peach