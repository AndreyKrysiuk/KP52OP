#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pupils.h"

int main(void) {
    char * fileName = "pupils.xml";
    pupils_t pupils = pupils_new();
    pupils_parseFromXML(pupils, fileName);
    pupils_print(pupils);
    pupils_remove(pupils);
    return 0;
}

