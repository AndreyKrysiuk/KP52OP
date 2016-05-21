#include <stdio.h>
#include <stdlib.h>

#include "turniket.h"

void reaction(worker_t worker, event_t event){
    printf("Worker %s bad guy that violates rules in time %i\n", worker_getName(worker), event_getTime(event));
}

int main()
{
    callback rc = reaction;
    turniket_t turniket = turniket_create(rc);
    worker_t worker1 = worker_new("Andrey Krysyuk", ALLOWED);
    worker_t worker2 = worker_new("Olga Yashan", ALLOWED);
    event_t event1 = event_new(worker1, 1000, INSIDE);
    event_t event2 = event_new(worker2, 1200, INSIDE);
    turniket_addEvent(turniket, event1);
    turniket_addEvent(turniket, event2);

    list_t * workersInside = turniket_getAllInside(turniket);
    puts("");
    for(int i = 0; i < list_getSize(workersInside); i++){
        printf("Inside: %s\n", worker_getName(event_getWorker(list_get(workersInside, i))));
    }
    puts("");

    list_t * forLastHour = list_new();
    int count = turniket_getEventsForLastHour(turniket,forLastHour, 1230);
    printf("Count events for last hour = %i\n", count);
    for(int i = 0; i < list_getSize(forLastHour); i++){
        printf("Last: %s at time %i\n", worker_getName(event_getWorker(list_get(forLastHour, i))), event_getTime(event2));
    }

     event_t event3 = event_new(worker1, 1200, OUTSIDE);
     turniket_addEvent(turniket, event3);
    printf("Time worker = %i\n\n", turniket_getWorkerTime(turniket, 500, 1500, worker1));

    turniket_delete(turniket);
    event_delete(event1);
    event_delete(event2);
    worker_delete(worker1);
    worker_delete(worker2);

    run_unit_tests();
}


