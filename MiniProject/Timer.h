#pragma once

#include <chrono>

using namespace std;

inline long long getElapsedMicroseconds(
    chrono::high_resolution_clock::time_point start,
    chrono::high_resolution_clock::time_point end)
{
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
