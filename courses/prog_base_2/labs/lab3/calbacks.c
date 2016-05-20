#include "callbacks.h"

void reaction1(user_t user, char * description){
    printf("%s, time of event has come: \n%s", user_getName(user), description);
}

void reaction2(user_t user, char * description){
    printf("User %s, you have reminder about event: \n%s", user_getName(user), description);
}

void reaction3(user_t user, char * description){
    printf("%s, one event soon: \n%s", user_getName(user), description);
}
