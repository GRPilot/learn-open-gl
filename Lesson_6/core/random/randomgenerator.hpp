//
// Created by gollan on 13.03.2021.
//

#ifndef LESSON_6_TEXTURES_RANDOMGENERATOR_HPP
#define LESSON_6_TEXTURES_RANDOMGENERATOR_HPP


class RandomGenerator {
    RandomGenerator();
public:
    RandomGenerator(const RandomGenerator &) = delete;
    RandomGenerator& operator=(const RandomGenerator &) = delete;

    static RandomGenerator &instance();

    long lnext(long min = nmin<long>(), long max = nmax<long>());
    unsigned long ulnext(unsigned long min = nmin<unsigned long>(),
                         unsigned long max = nmax<unsigned long>());
    double dnext(double min = nmin<double>(), double max = nmax<double>());
private:
    std::random_device r;

    template<class T> static T nmax() { return std::numeric_limits<T>::max(); }
    template<class T> static T nmin() { return std::numeric_limits<T>::min(); }
};


#endif //LESSON_6_TEXTURES_RANDOMGENERATOR_HPP
