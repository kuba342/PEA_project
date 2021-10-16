#pragma once
#ifndef clock_h
#define clock_h

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

class Clock {
private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;
public:

    Clock();
    ~Clock();

    void startTime();
    void endTime();
    long long executionTime();
};

#endif // !clock_h
