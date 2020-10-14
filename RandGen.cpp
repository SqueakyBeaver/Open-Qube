#include "RandGen.hpp"

float ran_gen::genRand(float low, float high) {
    static std::mt19937_64 random_gen(std::time(0));
    std::uniform_real_distribution<double> generate(low, high);
    return generate(random_gen);
}