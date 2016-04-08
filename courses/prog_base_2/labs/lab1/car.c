#include "car.h"

#define CAR_NUMBER 9
struct car_s{
    int speed;
    char carNumber[CAR_NUMBER];
};

car_t car_new(int speed){
    if(speed > 0 && speed < 600){
        car_t car = (car_t)malloc(sizeof(struct car_s));
        char carNumber[CAR_NUMBER];
        for(int i = 0; i < CAR_NUMBER - 1; i++){
            switch(i){
                case 0:
                case 1:
                case 6:
                case 7:
                    carNumber[i] = (char)(65+ rand()%26);
                    break;
                default:
                    carNumber[i] = (char)(48 + rand()%10);
                    break;
                }
        }
        strcpy(car->carNumber, carNumber);
        car->speed = speed;
        return car;
    } else return NULL;
}

int car_getSpeed(car_t car){
    return car->speed;
}

char * car_getNumber(car_t car){
    return car->carNumber;
}

void car_remove(car_t car){
    free(car);
    car = NULL;
}
