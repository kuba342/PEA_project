#include "Additional.h"

Additional::Additional() {};
Additional::~Additional() {};

bool Additional::isNum(std::string str) {
    for (int a = 0; a < str.length(); a++) {
        if (str[a] > '0' + 9 || str[a] < '0') return false;
    }
    return true;
}

int Additional::average(int* Tab, int size) {
    int sum = 0, average;
    for (int i = 0; i < size; i++) {
        sum += Tab[i];
    }
    return average = sum / size;
}

long long Additional::average(long long* Tab, int size) {
    long long sum = 0;
    long long average;
    for (int i = 0; i < size; i++) {
        sum += Tab[i];
    }
    return average = sum / size;
}