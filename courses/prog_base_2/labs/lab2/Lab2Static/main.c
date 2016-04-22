#include "programm_queue.h"

struct progQueue_s{
    int hours[MAX_QUEUE_SIZE];
    int size;
    int head;
};

progQueue_t progQueue_new(){
    progQueue_t queue = malloc(sizeof(struct progQueue_s));
    queue->size = 0;
    return queue;
}

void progQueue_remove(progQueue_t self){
    free(self);
}

void progQueue_enqueue(progQueue_t self, int value){
    if(value >= 0 && value <= 24){
        self->hours[self->size] = value;
        self->size++;
    } else return;
}

int progQueue_dequeue(progQueue_t self){
    if(self->size == 0)
        return 0;
    int del = self->hours[0];
    self->hours[0] = 0;
    for (i = 0; i < self->size; i++){
        self->hours[i] = self->hours[i+1];
    }
    self->size--;
    return del;
}

void progQueue_print(progQueue_t self){
    for(int i = 0; i < self->size; i++){
        printf("%2i ", self->hours[i]);
    }
}

int progQueue_getSize(progQueue_t self){
    return self->size;
}

