#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#define CAR_NUMBER 9
#define LENGTH_POST_NUMBER 5

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct car_s* car_t;

#include "core.h"
#include "posts.h"

car_t car_new(int speed);

char * car_getNumber(car_t car);

int car_getSpeed(car_t car);

void car_remove();

#endif // CAR_H_INCLUDED
