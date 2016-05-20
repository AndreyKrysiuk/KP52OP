#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

#include "user.h"

typedef enum{STATUS_OK, ERROR_NULL_POINTER, ERROR_INCORECT_DATA, ERROR_OVERFLOW} STATUS;

typedef struct event_s * event_t;

event_t event_new(user_t creator, char * description, int timeRemaindering);
void event_delete(event_t event);

char * event_getDescription(event_t event);
char * event_getCreatorName(event_t event);
char * event_getFollowerName(event_t event, int index);

user_t event_getCreator(event_t event);
user_t event_getFollower(event_t event, int index);

STATUS event_addFollower(event_t event, user_t follower);
int event_getTimeRemaindering(event_t event);
int event_getNumFollowers(event_t event);

void event_printFollowers(event_t event);
void event_printDescriptions(event_t event);
#endif // EVENTS_H_INCLUDED
