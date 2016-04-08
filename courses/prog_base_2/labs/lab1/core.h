#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

<<<<<<< HEAD
typedef struct core_s * core_t;
typedef struct violator_s * violator_t;

#include "posts.h"
#include "car.h"


core_t core_new();

=======
#include "posts.h"
#include "car.h"

typedef struct core_s * core_t;
typedef struct violator_s * violator_t;
typedef struct posts_s * posts_t;

core_t core_new();
>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6
void core_addNewViolator(core_t core, posts_t posts, int postIndex, car_t car);
void core_printViolatorsList(core_t core);
void core_remove(core_t core);

int core_getViolatorSpeed(core_t core, int index);
int core_getPostMaxSpeed(core_t core, int index);
char * core_getPostNumber(core_t core, int index);
char * core_getViolatorCarNumber(core_t core, int index);
int core_getAmountViolators(core_t core);

ERROR_CODE core_getErrorStatus(core_t core);

#endif // CORE_H_INCLUDED
<<<<<<< HEAD
=======

>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6
