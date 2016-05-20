#include "events.h"

struct event_s{
    user_t creator;
    user_t followers[10];
    char * description;
    int numFollowers;
    int timeRemaindering;
    STATUS code;
};

event_t event_new(user_t creator, char * description, int timeRemaindering){
    if(creator == NULL || strlen(description) == 0 || timeRemaindering < 0)
        return NULL;
    event_t event = malloc(sizeof(struct event_s));
    event->description = malloc(sizeof(char)*strlen(description));
    strcpy(event->description, description);
    event->numFollowers = 0;
    event->timeRemaindering = timeRemaindering;
    event->creator = creator;
    return event;
}

void event_delete(event_t event){
    free(event->description);
    free(event);
}

char * event_getDescription(event_t event){
    return event->description;
}

char * event_getCreatorName(event_t event){
    return user_getName(event->creator);
}

char * event_getFollowerName(event_t event, int index){
    return user_getName(event->followers[index]);
}


STATUS event_addFollower(event_t event, user_t follower){
    if(event->numFollowers >= 10)
        event->code = ERROR_OVERFLOW
        return;
    else if(event == NULL || follower == NULL)
        return ERROR_NULL_POINTER;
    else{
        event->followers[event->numFollowers] = follower;
        event->numFollowers++;
    }
}

void event_printFollowers(event_t event){
    for(int i = 0; i < event->numFollowers; i++){
        printf("Follower %i - %s\n", i+1, event_getFollowerName(event, i));
    }
}

int event_getTimeRemaindering(event_t event){
    return event->timeRemaindering;
}

user_t event_getCreator(event_t event){
    return event->creator;
}

void event_printDescriptions(event_t event){
    printf("Event: %s\n", event->description);
}

user_t event_getFollower(event_t event, int index){
    return event->followers[index];
}

int event_getNumFollowers(event_t event){
    return event->numFollowers;
}
