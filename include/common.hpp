#ifndef _COMMOM_HPP_
#define _COMMOM_HPP_

#include "solution.hpp"
#include <limits>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Infinity
const int INF = std::numeric_limits<int>::max();

// Shuffle vector
template <typename T>
void shuffle_vector(std::vector<T>& vec) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
}

// Get a random boolean
bool random_boolean();

// Get a random integer in [min, max]
int random_int(int min, int max);

// Get a random real number in [min, max]
double random_real(double min, double max);

#endif // !_COMMOM_HPP_
