#include "timer.hpp"

Timer::Timer() : m_begin(std::chrono::high_resolution_clock::now()) {
    // Empty
}

void Timer::reset() {
    m_begin = std::chrono::high_resolution_clock::now();
}

int64_t Timer::elapsed() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
}