#include <Timer.h>

using Clock = std::chrono::steady_clock;

Timer::Timer() noexcept : startTime(Clock::now()), endTime(startTime) {}

void Timer::start() noexcept {
    startTime = Clock::now();
}

void Timer::stop() noexcept {
    endTime = Clock::now();
}

double Timer::elapsedSeconds() const noexcept {
    return std::chrono::duration<double>(endTime - startTime).count();
}

long Timer::Nananoseconds() const noexcept {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
}