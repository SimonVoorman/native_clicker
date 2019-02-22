/*
 * Created by Simon
 * 2/19/2019
 */

#pragma once

#include "../includes.hpp"

// OPEN NAMESPACE c_win_api

class C_Win_Api {
public:
    DWORD get_kernel_32_address() {
        DWORD address = 0;

        __asm
        {
            mov ebx, fs:[0x30] ; get PEB
            mov ebx,[ebx + 0x0C]
            mov ebx,[ebx + 0x14]
            mov ebx,[ebx]
            mov ebx,[ebx]
            mov ebx,[ebx + 0x10] ; get kernel address
            mov address, ebx
        }

        return address;
    }

    PVOID get_proc_address(DWORD module, const char *proc_name);
    PVOID call_function(LPCTSTR psz_module, LPCTSTR psz_function, int arguments, ...);
};

// CLOSE NAMESPACE c_win_api
