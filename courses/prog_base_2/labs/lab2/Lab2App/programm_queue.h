#ifndef PROGRAMM_QUEUE_H_INCLUDED
#define PROGRAMM_QUEUE_H_INCLUDED

#define MAX_QUEUE_SIZE 49

typedef struct progQueue_s* progQueue_t;

progQueue_t progQueue_new();
void progQueue_remove(progQueue_t self);

void progQueue_enqueue(progQueue_t self, int value);
int progQueue_dequeue(progQueue_t self);
void progQueue_print(progQueue_t self);

int progQueue_getSize(progQueue_t self);
int progQueue_getHeadVal(progQueue_t self);
int progQueue_getTailVal(progQueue_t self);
int progQueue_getIndexVal(progQueue_t self, int index);

#endif // PROGRAMM_QUEUE_H_INCLUDED
