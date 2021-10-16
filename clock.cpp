#include "clock.h"

using namespace std;
using namespace std::chrono;

Clock::Clock() {}

Clock::~Clock() {}

void Clock::startTime() {
    start = high_resolution_clock::now();
}

void Clock::endTime() {
    end = high_resolution_clock::now();
}

long long Clock::executionTime() {
    return duration_cast<nanoseconds>(end - start).count();
}