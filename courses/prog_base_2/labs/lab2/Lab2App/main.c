#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>

#include "programm_queue.h"

typedef int (*check_f)(progQueue_t queue);
typedef char (*react_f)();

typedef struct dynamic_s {
    HANDLE hLib;
    check_f check;
    react_f react;
} dynamic_t;

dynamic_t * dynamic_init(const char * dllName);
void dynamic_clean(dynamic_t * dyn);

const char * userChoice();

int main(void) {
    progQueue_t queue = progQueue_new();

    const char * dllName = userChoice();
    dynamic_t * dll = dynamic_init(dllName);
    if (NULL == dll) {
        printf("Can't load dynamic!\n");
        return 1;
    }
    if (NULL == dll->check) {
        printf("Can't get compare function!\n");
        return 1;
    }
    if (NULL == dll->react) {
        printf("Can't get reaction function!\n");
        return 1;
    }
    printf("Dynamic loaded!");

    srand(time(NULL));

    for(int i = 0; i < 8; i++){
         progQueue_enqueue(queue, rand() % 25);
    }
    puts("");
    progQueue_print(queue);
    if(dll->check(queue) == 1)
        dll->react();
    else
        printf("OK\n");

    progQueue_remove(queue);
    dynamic_clean(dll);
    return 0;
}

const char * userChoice() {
    int dllNum = 0;
    while (dllNum < 1 || dllNum > 2) {
        printf("Choose DLL to load:\n1. Lab2DLL1\n2. Lab2DLL2\n> ");
        scanf("%i", &dllNum);
        if (dllNum == 1) {
            return "Lab2Dll1.dll";
        } else if (dllNum == 2) {
            return "Lab2Dll2.dll";
        }
        dllNum = 0;
    }
    return NULL;
}

dynamic_t * dynamic_init(const char * dllName) {
    dynamic_t * dyn = malloc(sizeof(struct dynamic_s));
    dyn->hLib = LoadLibrary(dllName);
    dyn->check = NULL;
    dyn->react = NULL;
    if (NULL != dyn->hLib) {
        dyn->check = (check_f)GetProcAddress(dyn->hLib, "check");
        dyn->react = (react_f)GetProcAddress(dyn->hLib, "reaction");
        return dyn;
    } else {
        return NULL;
    }
}

void dynamic_clean(dynamic_t * dyn) {
    FreeLibrary(dyn->hLib);
    free(dyn);
}
