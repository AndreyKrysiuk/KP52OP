#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#include "mutex.h"
#include "thread.h"
#include "setter.h"
#include "reader.h"

int main()
{
    symbol_t sharedData;
    sharedData.string = "fsd14afaff123457fadf64df";
    sharedData.symbol = '\0';
    sharedData.mu = mutex_new();
    setter_t setter1 = setter_create(&sharedData);
    setter_t setter2 = setter_create(&sharedData);
    reader_t reader1 = reader_create(&sharedData);
    reader_t reader2 = reader_create(&sharedData);
    reader_t reader3 = reader_create(&sharedData);
    mutex_free(sharedData.mu);
    setter_remove(setter1);
    setter_remove(setter2);
    reader_remove(reader1);
    reader_remove(reader2);
    reader_remove(reader3);
    return 0;
}
