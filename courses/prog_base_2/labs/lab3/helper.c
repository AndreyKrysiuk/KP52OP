#include "helper.h"

struct helper_s{
    event_t events[5];
    int numEvents;
};

helper_t helper_new(){
    helper_t helper = malloc(sizeof(struct helper_s));
    helper->numEvents = 0;
    return helper;
}

void helper_delete(helper_t helper){
    free(helper);
}

int helper_addEvent(helper_t helper, event_t event){
    if(helper->numEvents < 5 && event != NULL){
        helper->events[helper->numEvents] = event;
        helper->numEvents++;
        return 1;
    } else {
        return 0;
    }
}

static void helper_message(event_t event, user_t reciver){
     user_getCB(reciver)(reciver, event_getDescription(event));
}

void helper_reminder(helper_t helper){
    int count = 0;
    int numEvents = 0;
    while(numEvents < helper->numEvents){
        for(int i = 0; i < helper->numEvents; i++){
            if(count == event_getTimeRemaindering(helper->events[i])){
                helper_message(helper->events[i], event_getCreator(helper->events[i]));
                if(event_getNumFollowers(helper->events[i]) != 0){
                    for(int k = 0; k < event_getNumFollowers(helper->events[i]); k++){
                        helper_message(helper->events[i], event_getFollower(helper->events[i], k));
                    }
                }
                numEvents++;
            }
        }
        count++;
    }
}

int helper_getNumEvents(helper_t helper){
    return helper->numEvents;
}
