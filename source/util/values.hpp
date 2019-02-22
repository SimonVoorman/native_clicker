/*
 * Created by Simon
 * 2/19/2019
 */

#pragma once

// OPEN NAMESPACE values

#include "../includes.hpp"
#include "c_rand_util.hpp"
#include "c_win_api.hpp"

namespace G
{
    extern C_Rand_Util rand_util;

    extern C_Win_Api win_util;

    extern int min_cps;
    extern int max_cps;

    extern bool enabled;
}

// CLOSE NAMESPACE values
