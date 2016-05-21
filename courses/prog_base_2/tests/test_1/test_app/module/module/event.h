#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED

#include "worker.h"

typedef enum{INSIDE, OUTSIDE} STATE;

typedef struct event_s * event_t;

event_t event_new(worker_t worker, int time, STATE state);

worker_t event_getWorker(event_t event);

int event_getTime(event_t event);

STATE event_getState(event_t event);
void event_delete(event_t event);

#endif // EVENT_H_INCLUDED
