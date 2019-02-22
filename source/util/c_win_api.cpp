/*
 * Created by Simon
 * 2/19/2019
 */

#include "c_win_api.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"
void *C_Win_Api::get_proc_address(DWORD module, const char *proc_name)
{
    auto *modb = (char*) module;
    auto *dos_header = (IMAGE_DOS_HEADER*) modb;
    auto *nt_headers = (IMAGE_NT_HEADERS*) (modb + dos_header->e_lfanew);
    IMAGE_OPTIONAL_HEADER *opt_header = &nt_headers->OptionalHeader;
    auto *exp_entry = &opt_header->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    auto *exp_dir = (IMAGE_EXPORT_DIRECTORY*) (modb + exp_entry->VirtualAddress);
    auto **func_table = (void**) (modb + exp_dir->AddressOfFunctions);
    auto *ord_table = (WORD*) (modb + exp_dir->AddressOfNameOrdinals);
    auto **name_table = (char**) (modb + exp_dir->AddressOfNames);
    void *address = nullptr;

    DWORD i;

    if (((DWORD) proc_name >> 16) == 0)
    {
        WORD ordinal = LOWORD(proc_name);
        DWORD ord_base = exp_dir->Base;

        if (ordinal < ord_base || ordinal > ord_base + exp_dir->NumberOfFunctions)
        {
            return nullptr;
        }

        address = (void*) (modb + (DWORD) func_table[ordinal - ord_base]);
    }
    else
    {
        for (i = 0; i < exp_dir->NumberOfNames; i++)
        {
            if (strcmp(proc_name, modb + (DWORD) name_table[i]) == 0)
            {
                address = (void*) (modb + (DWORD) func_table[ord_table[i]]);
            }
        }
    }

    if ((char*) address >= (char*) exp_dir && (char*) address < (char*) exp_dir + exp_entry->Size)
    {
        char *dll_name, *func_name;

        HMODULE frwd_module;

        dll_name = _strdup((char*) address);

        if (!dll_name)
        {
            return nullptr;
        }

        address = nullptr;

        func_name = strchr(dll_name, '.');

        *func_name++ = 0;

        static std::string module_handle_a = enc_str("GetModuleHandleA");

        // called with asm
        auto get_module_handle = (DWORD) get_proc_address(get_kernel_32_address(), module_handle_a.data());

        __asm
        {
            push dll_name
            call get_module_handle
            mov frwd_module, eax
        }

        if (!frwd_module)
        {
            static std::string sLoadLibA = enc_str("LoadLibraryA");

            // called with asm
            auto load_library = (DWORD)get_proc_address(get_kernel_32_address(), sLoadLibA.data());

            __asm
            {
                push dll_name
                call DWORD PTR load_library
                mov frwd_module, eax
            }
        }

        if (frwd_module)
        {
            address = get_proc_address((DWORD) frwd_module, func_name);
        }

        free(dll_name);
    }

    return address;
}

PVOID C_Win_Api::call_function(LPCTSTR psz_module, LPCTSTR psz_function, int arguments, ...)
{
    HANDLE module;

    static std::string load_library_a = enc_str("LoadLibraryA");

    auto load_library = (DWORD) get_proc_address(get_kernel_32_address(), load_library_a.data());
    PVOID ret;

    __asm
    {
        push psz_module
        call load_library
        mov module, eax
    }

    if (!module)
    {
        return nullptr;
    }

    auto function_address = (DWORD) get_proc_address((DWORD) module, psz_function);

    if (!function_address)
    {
        return nullptr;
    }

    va_list params;
    void* param;
    va_start(params, arguments);

    for (int ax = 0; ax < arguments; ax++)
    {
        param = va_arg(params, void*);
        __asm
        {
            push param
        }
    }

    __asm
    {
        call DWORD PTR function_address
        mov ret, eax
    }

    va_end(params);

    return ret;
}
