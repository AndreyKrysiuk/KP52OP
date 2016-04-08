#ifndef POSTS_H_INCLUDED
#define POSTS_H_INCLUDED



typedef enum{VIOLATOR, OK} VIOLATOR_STATUS;
typedef enum errors{STATUS_OK, STATUS_ERROR} ERROR_CODE;

#include "core.h"
#include "car.h"

typedef struct posts_s* posts_t;
typedef struct post_s* post_t;
typedef struct core_s* core_t;
typedef struct car_s* car_t;

posts_t posts_new();

void posts_addNewPost(posts_t self, int maxAllowSpeed);
void posts_printInfoAboutPosts(posts_t self);
void posts_remove(posts_t self);

int posts_getPostMaxSpeed(posts_t self, int postIndex);
int posts_getAmountPosts(posts_t self);

char * posts_getPostNumber(posts_t self, int postIndex);

ERROR_CODE posts_getErrorCode(posts_t self);

VIOLATOR_STATUS posts_checkViolator(posts_t self, int postIndex, car_t car, core_t core);

#endif // POSTS_H_INCLUDED
