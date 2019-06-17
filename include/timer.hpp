#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <chrono>

class Timer {
public:
    // Constructor
    Timer();

    // Reset the start time
    void reset();

    int64_t elapsed() const;
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

#endif // !_TIMER_HPP_
