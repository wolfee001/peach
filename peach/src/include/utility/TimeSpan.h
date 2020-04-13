#pragma once

#include <cinttypes>

namespace peach {

class TimeSpan {
public:
    TimeSpan(uint32_t microseconds = 0);

    uint32_t GetNanoeconds() const;
    float GetMilliseconds() const;
    float GetSeconds() const;
    operator float() const;

    TimeSpan operator+(const TimeSpan& other) const;
    TimeSpan& operator+=(const TimeSpan& other);

    TimeSpan operator-(const TimeSpan& other) const;
    TimeSpan& operator-=(const TimeSpan& other);

private:
    uint32_t mMicroseconds = 0;
};

}