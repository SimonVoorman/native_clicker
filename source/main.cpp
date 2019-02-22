#include <iostream>
#include "includes.hpp"
#include "util/c_win_api.hpp"
#include "util/values.hpp"

int main()
{
    G::win_util.call_function(enc_str("USER32.dll"), enc_str("MessageBoxA"), 4, nullptr, enc_str("Caption"), enc_str("Text"), MB_OK);
    return 0;
}