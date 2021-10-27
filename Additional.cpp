#include "Additional.h"
#include <string>

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

unsigned long long Additional::Newton(unsigned long long n, unsigned long long k) {
    if (k > n) {
        return 0;
    }
    if (k == n || k == 0) {
        return 1;
    }
    unsigned long long result = 1;
    for (unsigned long long i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }
    return result;
}