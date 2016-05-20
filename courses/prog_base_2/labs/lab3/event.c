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
    if(creator == NULL || strlen(description) == 0 || timeRemaindering < 0){
        return NULL;
    }
    event_t event = malloc(sizeof(struct event_s));
    event->description = malloc(sizeof(char)*strlen(description));
    strcpy(event->description, description);
    event->numFollowers = 0;
    event->timeRemaindering = timeRemaindering;
    event->creator = creator;
    event->code = STATUS_OK;
    return event;
}

void event_delete(event_t event){
    if(event == NULL)
        return;
    free(event->description);
    free(event);
}

char * event_getDescription(event_t event){
    if(event != NULL)
        return event->description;
}

char * event_getCreatorName(event_t event){
    if(event != NULL)
        return user_getName(event->creator);
}

char * event_getFollowerName(event_t event, int index){
    if(event == NULL)
        return "";
    else if(index < 0 || index >= event->numFollowers)
        event->code = ERROR_INCORECT_DATA;
    else
        return user_getName(event->followers[index]);
}


void event_addFollower(event_t event, user_t follower){
    if(event->numFollowers >= 10)
        event->code = ERROR_OVERFLOW;
    else if(event == NULL || follower == NULL)
        event->code = ERROR_NULL_POINTER;
    else{
        event->followers[event->numFollowers] = follower;
        event->numFollowers++;
        event->code = STATUS_OK;
    }
}

void event_printFollowers(event_t event){
    if(event != NULL){
        for(int i = 0; i < event->numFollowers; i++){
            printf("Follower %i - %s\n", i+1, event_getFollowerName(event, i));
        }
    }
}

int event_getTimeRemaindering(event_t event){
    if(event != NULL)
        return event->timeRemaindering;
}

user_t event_getCreator(event_t event){
    if(event != NULL)
        return event->creator;
}

void event_printDescriptions(event_t event){
    if(event != NULL)
        printf("Event: %s\n", event->description);
}

user_t event_getFollower(event_t event, int index){
    if(index < 0 || index > event->numFollowers){
        event->code = ERROR_INCORECT_DATA;
        return NULL;
    }
    else
        return event->followers[index];
}

int event_getNumFollowers(event_t event){
    if(event != NULL)
        return event->numFollowers;
}

STATUS event_getStatus(event_t event){
    if(event != NULL)
        return event->code;
}
