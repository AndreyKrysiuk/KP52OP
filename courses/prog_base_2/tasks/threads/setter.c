#include "setter.h"

struct setter_s{
    thread_t * th;
};

setter_t setter_create(symbol_t* data){
    setter_t new_setter = malloc(sizeof(struct setter_s));
    new_setter->th = thread_create_args(symbolSetter, data);
    return new_setter;
}
void * symbolSetter(void * args) {
    symbol_t * setter = (symbol_t *)args;
    int i = 0;
    while(1){
        mutex_lock(setter->mu);
        setter->symbol = setter->string[i];
        mutex_unlock(setter->mu);
        if(i < strlen(setter->string)){
            i++;

        } else if(i == strlen(setter->string)){
            i = 0;
        }
    }
    return NULL;
}

void setter_remove(setter_t setter){
    thread_free(setter->th);
    free(setter);
}
