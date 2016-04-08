#include "posts.h"

#define MAX_AMOUNT_POST 50
#define LENGTH_POST_NUMBER 5

struct post_s{
    int maxAllowSpeed;
    char postNumber[LENGTH_POST_NUMBER];
};

struct posts_s{
    int amountPosts;
    ERROR_CODE error_status;
    post_t posts[MAX_AMOUNT_POST];
};

posts_t posts_new(){
    posts_t posts = (posts_t)malloc(sizeof(struct posts_s));
    posts->amountPosts = 0;
    posts->error_status = STATUS_OK;
    return posts;
}

void posts_addNewPost(posts_t self, int maxAllowSpeed){
    if(self->amountPosts < MAX_AMOUNT_POST){
        if(maxAllowSpeed > 0 && maxAllowSpeed <= 180){
            self->posts[self->amountPosts] = (post_t)malloc(sizeof(struct post_s));
            char postNumber[LENGTH_POST_NUMBER];
            for(int i = 0; i < LENGTH_POST_NUMBER - 1; i++){
                switch(i){
                    case 0:
                        postNumber[i] = (char)(65+ rand()%26);
                        break;
                    default:
                        postNumber[i] = (char)(48 + rand()%10);
                        break;
                }
            }
            strcpy(self->posts[self->amountPosts]->postNumber, postNumber);
            self->posts[self->amountPosts]->maxAllowSpeed = maxAllowSpeed;
            self->amountPosts++;
            self->error_status = STATUS_OK;
        } else self->error_status = STATUS_ERROR;
    } else self->error_status = STATUS_ERROR;
}

void posts_printInfoAboutPosts(posts_t self){
   for(int i = 0; i < self->amountPosts; i++){
        printf("%s: maxSpeed = %d\n", self->posts[i]->postNumber, self->posts[i]->maxAllowSpeed);
   }
}

VIOLATOR_STATUS posts_checkViolator(posts_t self, int postIndex, car_t car, core_t core){
    if(postIndex >= 0 && postIndex < self->amountPosts){
        if(car_getSpeed(car) > self->posts[postIndex]->maxAllowSpeed){
            core_addNewViolator(core, self, postIndex, car);
            self->error_status = STATUS_OK;
            return VIOLATOR;
        } else {
            self->error_status = STATUS_OK;
            return OK;
        }
    } else self->error_status = STATUS_ERROR;
}

char * posts_getPostNumber(posts_t self, int postIndex){
    if(postIndex >= 0 && postIndex < self->amountPosts){
        self->error_status = STATUS_OK;
        return self->posts[postIndex]->postNumber;
    } else self->error_status = STATUS_ERROR;
}

int posts_getPostMaxSpeed(posts_t self, int postIndex){
    if(postIndex >= 0 && postIndex < self->amountPosts){
        self->error_status = STATUS_OK;
        return self->posts[postIndex]->maxAllowSpeed;
    } else self->error_status = STATUS_ERROR;
}

void posts_remove(posts_t self){
    for(int i = 0; i < self->amountPosts; i++){
        free(self->posts[i]);
    }
    free(self);
}

int posts_getAmountPosts(posts_t self){
    return self->amountPosts;
}

ERROR_CODE posts_getErrorCode(posts_t self){
    return self->error_status;
}
