#include <utility/Timer.h>

namespace peach {

Timer::Timer()
    : mCreationTime(std::chrono::high_resolution_clock::now())
    , mLastTick(mCreationTime)
{
}

TimeSpan Timer::Tick()
{
    const auto now = std::chrono::high_resolution_clock::now();
    const TimeSpan ts(static_cast<uint32_t>(std::chrono::duration<double, std::micro>(now - mLastTick).count()));
    mLastTick = now;
    return ts;
}

TimeSpan Timer::Total()
{
    const auto now = std::chrono::high_resolution_clock::now();
    return TimeSpan(static_cast<uint32_t>(std::chrono::duration<double, std::micro>(now - mCreationTime).count()));
}

void Timer::Reset()
{
    mCreationTime = std::chrono::high_resolution_clock::now();
    mLastTick = mCreationTime;
}

} // namespace peach