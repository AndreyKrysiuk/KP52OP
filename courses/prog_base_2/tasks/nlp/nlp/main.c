#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "nlp.h"

int main()
{
    text_t text = text_parse(text_readText("text.txt"));
    list_t * unique =  text_getUnigueWords(text);
    text_writeUniqueInFile(unique);
    return 0;
}
