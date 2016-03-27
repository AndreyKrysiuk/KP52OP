#include "reader.h"

struct reader_s{
    thread_t * th;
};

reader_t reader_create(symbol_t* data){
    reader_t new_reader = malloc(sizeof(struct reader_s));
    new_reader->th = thread_create_args(digitReader, data);
    thread_join(new_reader->th);
    return new_reader;
}

void * digitReader(void * args){
    symbol_t * reader = (symbol_t *)args;
    while (1) {
        mutex_lock(reader->mu);
        if(isdigit(reader->symbol) != 0) {
            printf("%c is digit\n", reader->symbol);
        }
        mutex_unlock(reader->mu);
    }
    return NULL;
}

void reader_remove(reader_t reader){
    thread_free(reader->th);
    free(reader);
}
