#ifndef TURNIKET_H_INCLUDED
#define TURNIKET_H_INCLUDED

#include <stdlib.h>
#include "list.h"
#include "worker.h"
#include "event.h"

typedef struct turniket_s * turniket_t;

typedef void (*callback)(worker_t worker, event_t event);

turniket_t turniket_create(callback react);
void turniket_delete(turniket_t turniket);
void turniket_addWorker(turniket_t turniket, worker_t worker);
void turniket_addEvent(turniket_t turniket, event_t event);

list_t * turniket_getAllInside(turniket_t turniket);

int turniket_getEventsForLastHour(turniket_t turniket, list_t * eventsHour, int nowTime);
int turniket_getWorkerTime(turniket_t turniket, int minTime, int maxTime, worker_t worker);
event_t turniket_getEvent(turniket_t turniket, int index);
worker_t turniket_getWorker(turniket_t turniket, int index);
void turniket_BlockWorker(turniket_t turniket, int index);
#endif // TURNIKET_H_INCLUDED
