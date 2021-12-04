#pragma once
#ifndef Additional_h
#define Additional_h

#include <string>

class Additional {
public:
    Additional();
    ~Additional();
    bool isNum(std::string str);
    bool isDouble(std::string str);
    int average(int* Tab, int size);
    long long average(long long* Tab, int size);
    unsigned long long Newton(unsigned long long n, unsigned long long k);
};

#endif