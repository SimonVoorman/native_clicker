/*
 * Created by Simon
 * 2/20/2019
 */
#include "../includes.hpp"

#define SELF_DESTRUCT_KEY = VK_F8;

DWORD WINAPI auto_clicker_thread(LPVOID param)
{
    /*while (!GetAsyncKeyState(SELF_DESTRUCT_KEY))
    {

    }*/

    exit(0);
}

void C_Clicker::setup_threads()
{
    CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(auto_clicker_thread), nullptr, 0, nullptr);
}
