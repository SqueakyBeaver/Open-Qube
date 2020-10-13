#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <chrono>
#include <random>

namespace ran_gen {
// Generate a random number
float genRand(float low, float high);

// Optional seed
float genRand(float low, float high, int seed);
} // namespace ran_gen

#endif