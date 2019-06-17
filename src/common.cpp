#include "common.hpp"
#include <random>
#include <chrono>

// Get a random boolean
bool random_boolean() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    if (engine() % 2 == 1) {
        return true;
    }
    else {
        return false;
    }
}

// Get a random integer in [min, max]
int random_int(int min, int max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_int_distribution<int> uni(min, max);
    return uni(engine);
}

// Get a random real number in [min, max]
double random_real(double min, double max) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine engine(seed);
    std::uniform_real_distribution<double> uni(min, max);
    return uni(engine);
}