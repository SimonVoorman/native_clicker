/*
 * Created by Simon
 * 2/19/2019
 */

#pragma once

#include "../includes.hpp"

// OPEN NAMESPACE C_Rand_Util

class C_Rand_Util {
public:

    float random_float(const float min, const float max)
    {
        static std::random_device random_device;
        static std::mt19937 gen(random_device());

        static std::uniform_real_distribution<> dis(min, max);

        return static_cast<float>(dis(gen));
    }
};

// CLOSE NAMESPACE C_Rand_Util
