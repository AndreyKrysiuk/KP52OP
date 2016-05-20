#include "user.h"

struct user_s{
    char name[30];
    callback reaction;
};

user_t user_new(char * name, callback rc){
    if(strlen(name) < 30 || rc != NULL){
        user_t user = malloc(sizeof(struct user_s));
        strcpy(user->name, name);
        user->reaction = rc;
        return user;
    } else {
        return NULL;
    }
}

char * user_getName(user_t user){
    return user->name;
}

callback user_getCB(user_t user){
    return user->reaction;
}
void user_delete(user_t user){
    free(user);
}
