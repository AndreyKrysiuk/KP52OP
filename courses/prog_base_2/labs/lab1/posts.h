#ifndef POSTS_H_INCLUDED
#define POSTS_H_INCLUDED

<<<<<<< HEAD

=======
#include "core.h"
#include "car.h"
>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6

typedef enum{VIOLATOR, OK} VIOLATOR_STATUS;
typedef enum errors{STATUS_OK, STATUS_ERROR} ERROR_CODE;

typedef struct posts_s* posts_t;
typedef struct post_s* post_t;
<<<<<<< HEAD

#include "core.h"
#include "car.h"


=======
typedef struct core_s* core_t;
typedef struct car_s* car_t;
>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6

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
<<<<<<< HEAD
=======

>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6
