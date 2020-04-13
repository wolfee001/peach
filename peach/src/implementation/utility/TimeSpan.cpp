#include <utility/TimeSpan.h>

namespace peach {

TimeSpan::TimeSpan(uint32_t microseconds /* = 0 */)
    : mMicroseconds(microseconds)
{
}

uint32_t TimeSpan::GetNanoeconds() const { return mMicroseconds; }

float TimeSpan::GetMilliseconds() const
{
    static constexpr float divider = 0.001F;
    return static_cast<float>(mMicroseconds) * divider;
}

float TimeSpan::GetSeconds() const
{
    static constexpr float divider = 0.001F * 0.001F;
    return static_cast<float>(mMicroseconds) * divider;
}

TimeSpan::operator float() const { return GetMilliseconds(); }

TimeSpan TimeSpan::operator+(const TimeSpan& other) const { return { mMicroseconds + other.mMicroseconds }; }

TimeSpan& TimeSpan::operator+=(const TimeSpan& other)
{
    mMicroseconds += other.mMicroseconds;
    return *this;
}

TimeSpan TimeSpan::operator-(const TimeSpan& other) const { return { mMicroseconds - other.mMicroseconds }; }
TimeSpan& TimeSpan::operator-=(const TimeSpan& other)
{
    mMicroseconds -= other.mMicroseconds;
    return *this;
}

} // namespace peach