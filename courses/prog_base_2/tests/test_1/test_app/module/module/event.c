#include "event.h"

struct event_s{
    worker_t worker;
    int time;
    STATE state;
};

event_t event_new(worker_t worker, int time, STATE state){
    event_t event = malloc(sizeof(struct event_s));
    event->worker = worker;
    event->time = time;
    event->state = state;
}

worker_t event_getWorker(event_t event){
    return event->worker;
}

int event_getTime(event_t event){
    return event->time;
}

STATE event_getState(event_t event){
    return event->state;
}

void event_delete(event_t event){
    free(event);
}
