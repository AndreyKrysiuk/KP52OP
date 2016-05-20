#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct user_s * user_t;
typedef void (*callback)(user_t user, char* description);

user_t user_new(char * name, callback rc);

char * user_getName(user_t user);

callback user_getCB(user_t user);

void user_delete(user_t user);

#endif // USER_H_INCLUDED
