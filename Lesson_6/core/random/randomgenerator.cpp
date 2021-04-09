//
// Created by gollan on 13.03.2021.
//

#include "deps.hpp"

#include "randomgenerator.hpp"

RandomGenerator::RandomGenerator() = default;

RandomGenerator &RandomGenerator::instance() {
    static RandomGenerator randGenerator;
    return randGenerator;
}
long RandomGenerator::lnext(long min, long max) {
    std::uniform_int_distribution<long> dist(min, max);
    std::mt19937 gen(r());
    return dist(gen);
}

unsigned long RandomGenerator::ulnext(unsigned long min, unsigned long max) {
    std::uniform_int_distribution<unsigned long> dist(min, max);
    std::mt19937 gen(r());
    return dist(gen);
}

double RandomGenerator::dnext(double min, double max) {
    std::uniform_real_distribution<> dist(min, max);
    std::mt19937 gen(r());
    return dist(gen);
}