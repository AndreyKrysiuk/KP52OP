#include "turniket.h"

struct turniket_s{
    list_t * event;
    list_t * workers;
    callback react;
};

turniket_t turniket_create(callback react){
    turniket_t turniket = malloc(sizeof(struct turniket_s));
    turniket->react = react;
    turniket->workers = list_new();
    turniket->event = list_new();
    return turniket;
}

void turniket_addWorker(turniket_t turniket, worker_t worker){
    list_push_back(turniket->workers, worker);
}

void turniket_addEvent(turniket_t turniket, event_t event){
    if(list_getSize(turniket->event) != 0){
        for(int i = 0; i < list_getSize(turniket->event); i++){
            if(worker_getName(event_getWorker(event)) == worker_getName(event_getWorker(list_get(turniket->event, i)))){
                if(event_getState(event) == event_getState(turniket_getEvent(turniket, i))){
                    turniket->react(event_getWorker(event),event);
                    return;
                }
            }
        }
    }
    if(worker_getStatus(event_getWorker(event)) == BLOCKED){
        printf("Worker %s can't go\n", worker_getName(event_getWorker(event)));
    } else {
        list_push_back(turniket->event, event);
    }
}

int turniket_getEventsForLastHour(turniket_t turniket, list_t * eventsHour, int nowTime){
    int count = 0;
    for(int i = 0; i < list_getSize(turniket->event); i++){
        if(event_getTime(turniket_getEvent(turniket, i)) >= nowTime - 60 && event_getTime(turniket_getEvent(turniket, i)) <= nowTime){
                list_push_back(eventsHour, turniket_getEvent(turniket, i));
                count++;
           }
    }
    return count;
}

int turniket_getWorkerTime(turniket_t turniket, int minTime, int maxTime, worker_t worker){
    int time = 0;
    int leftLim;
    int rightLim;
    for(int i = 0; i < list_getSize(turniket->event); i++){
        if(event_getWorker(turniket_getEvent(turniket, i)) == worker){
            if(event_getTime(turniket_getEvent(turniket, i)) >= minTime
               && event_getTime(turniket_getEvent(turniket, i)) <= maxTime){
                if(event_getState(turniket_getEvent(turniket, i)) == INSIDE){
                    leftLim = event_getTime(turniket_getEvent(turniket, i));
                } else if(event_getState(turniket_getEvent(turniket, i)) == OUTSIDE)
                    rightLim = event_getTime(turniket_getEvent(turniket, i));
                }
            time = rightLim - leftLim;
        }
    }
    return time;
}

list_t * turniket_getAllInside(turniket_t turniket){
    list_t * workersInside = list_new();
    for(int i = 0; i < list_getSize(turniket->event); i++){
        if(event_getState(turniket_getEvent(turniket, i)) == INSIDE){
               list_push_back(workersInside, turniket_getEvent(turniket,i));
        }
    }
    return workersInside;
}

event_t turniket_getEvent(turniket_t turniket, int index){
    return list_get(turniket->event, index);
}

worker_t turniket_getWorker(turniket_t turniket, int index){
    return list_get(turniket->workers, index);
}

void turniket_BlockWorker(turniket_t turniket, int index){
    worker_setStatus(list_get(turniket->workers, index), BLOCKED);
}



void turniket_delete(turniket_t turniket){
    list_free(turniket->workers);
    list_free(turniket->event);
    free(turniket);
}
