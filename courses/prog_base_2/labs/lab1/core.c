#include "core.h"

#define MAX_AMOUNT_VIOLATORS 100

struct core_s{
    int amountViolators;
    ERROR_CODE error;
    violator_t violators[MAX_AMOUNT_VIOLATORS];
};

struct violator_s{
    int speedViolator;
    int maxAllowSpeedOnPost;
    char * postNumber;
    char * violatorCarNumber;
};

core_t core_new(){
    core_t new_core = malloc(sizeof(struct core_s));
    new_core->error = STATUS_OK;
    new_core->amountViolators = 0;
    return new_core;
}

void core_addNewViolator(core_t core, posts_t posts, int postIndex, car_t car){
    if(postIndex > 0 && postIndex < posts_getAmountPosts(posts)){
        core->violators[core->amountViolators] = malloc(sizeof(struct violator_s));
        core->violators[core->amountViolators]->postNumber = malloc(sizeof(char)*LENGTH_POST_NUMBER);
        core->violators[core->amountViolators]->violatorCarNumber = malloc(sizeof(char)*CAR_NUMBER);
        core->violators[core->amountViolators]->speedViolator = car_getSpeed(car);
        core->violators[core->amountViolators]->maxAllowSpeedOnPost = posts_getPostMaxSpeed(posts, postIndex);
        core->violators[core->amountViolators]->postNumber = posts_getPostNumber(posts, postIndex);
        core->violators[core->amountViolators]->violatorCarNumber = car_getNumber(car);
        core->amountViolators++;
        core->error = STATUS_OK;
    } else core->error = STATUS_ERROR;
}

void core_printViolatorsList(core_t core){
    for(int i = 0; i < core->amountViolators; i++){
        printf("Violator - %s speed = %d (> max = %d) on post number %s\n", core->violators[i]->violatorCarNumber, core->violators[i]->speedViolator, core->violators[i]->maxAllowSpeedOnPost, core->violators[i]->postNumber);
    }
}

void core_remove(core_t core){
    for(int i = 0; i < core->amountViolators; i++){
        free(core->violators[i]->postNumber);
        free(core->violators[i]->violatorCarNumber);
        free(core->violators[i]);
    }
    free(core);
}
