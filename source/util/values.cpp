#include "values.hpp"
#include "c_rand_util.hpp"
#include "c_win_api.hpp"

/*
 * Created by Simon
 * 2/19/2019
 */

C_Rand_Util G::rand_util;
C_Win_Api G::win_util;

int G::min_cps = 0;
int G::max_cps = 0;

bool G::enabled = false;