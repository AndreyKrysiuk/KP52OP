#include "main.h"
#include <stdio.h>

int DLL_EXPORT check(progQueue_t self){
    int countDays = 0;
    while(progQueue_getSize(self) != 0){
        if(progQueue_dequeue(self) < 3)
            countDays++;
    }
    if(countDays >= 2)
        return 1;
    else
        return 0;
}

void DLL_EXPORT reaction(){
    printf("FIRED!!!\n");
}

extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
