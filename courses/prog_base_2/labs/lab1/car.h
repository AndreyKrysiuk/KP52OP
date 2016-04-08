#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#define CAR_NUMBER 9
#define LENGTH_POST_NUMBER 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

<<<<<<< HEAD
typedef struct car_s* car_t;

#include "core.h"
#include "posts.h"


=======
#include "core.h"
#include "posts.h"

typedef struct car_s* car_t;
>>>>>>> 3bcd7c215158b6612b1e77901692b9b6bbf312a6

car_t car_new(int speed);

char * car_getNumber(car_t car);

int car_getSpeed(car_t car);

void car_remove();

#endif // CAR_H_INCLUDED
