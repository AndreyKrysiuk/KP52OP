#include <stdio.h>
#include <stdlib.h>

#include "module.h"

#define MAX_AMOUNT_POSTS 50
#define MAX_LENGTH_POST 100

struct post_s{
    int amountReposts;
    char * text;
};

struct network_s{
    ERROR_CODE error;
    int amountPosts;
    post_t posts[MAX_AMOUNT_POSTS];
};

network_t network_create(){
    network_t new_network = malloc(sizeof(struct network_s));
    new_network->error = NO_ERROR;
    new_network->amountPosts = 0;
    return new_network;
}

void network_addNewPostToEnd(network_t self, int amountReposts, const char* text){
    if(amountReposts < 0){
        self->error = WRONG_AMOUNT_REPOSTS;
    } else if(strlen(text) > MAX_LENGTH_POST){
        self->error = WRONG_LENGTH_POST;
    } else {
        self->error = NO_ERROR;
        self->posts[self->amountPosts] = malloc(sizeof(struct post_s));
        self->posts[self->amountPosts]->text = malloc(sizeof(char) * MAX_LENGTH_POST);
        self->posts[self->amountPosts]->amountReposts = amountReposts;
        self->posts[self->amountPosts]->text = text;
        self->amountPosts++;
    }
}

void network_addNewPostByIndex(network_t self, int amountReposts, const char* text, int index){
    if(index >= 0 && index <= self->amountPosts){
        if(amountReposts < 0){
            self->error = WRONG_AMOUNT_REPOSTS;
        } else if(strlen(text) > MAX_LENGTH_POST){
            self->error = WRONG_LENGTH_POST;
            } else {
                self->error = NO_ERROR;
                if(index == self->amountPosts){
                    network_addNewPostToEnd(self, amountReposts, text);
                } else {
                    self->posts[self->amountPosts] = malloc(sizeof(struct post_s));
                    self->posts[self->amountPosts]->text = malloc(sizeof(char) * MAX_LENGTH_POST);
                    self->posts[self->amountPosts]->amountReposts = amountReposts;
                    self->posts[self->amountPosts]->text = text;
                    post_t tmp;
                    for(int i = self->amountPosts; i > index; i--){
                        tmp = self->posts[i];
                        self->posts[i] = self->posts[i - 1];
                        self->posts[i - 1] = tmp;
                    }
                    self->amountPosts++;
                }
            }
        } else self->error = WRONG_INDEX;
}

void network_removePostByIndex(network_t self, int index){
    if (self->amountPosts == 0){
        self->error = NETWORK_EMPTY;
    } else {
        self->error = NO_ERROR;
        if(index >= 0 && index < self->amountPosts){
            if(index == self->amountPosts - 1){
                free(self->posts[index]->text);
                free(self->posts[index]);
                self->amountPosts--;
            } else {
                post_t tmp;
                for(int i = index; i < self->amountPosts; i++){
                    tmp = self->posts[i];
                    self->posts[i] = self->posts[i + 1];
                    self->posts[i + 1] = tmp;
                }
                free(self->posts[self->amountPosts]->text);
                free(self->posts[self->amountPosts]);
                self->amountPosts--;
            }
        } else self->error = WRONG_INDEX;
    }
}

int network_getAmountRepostsOfPost(network_t self, int index){
    if(index >= 0 && index < self->amountPosts){
        self->error = NO_ERROR;
        return self->posts[index]->amountReposts;
    }
    else self->error = WRONG_INDEX;
}

int network_getAmountPosts(network_t self){
    return self->amountPosts;
}

void network_printPost(network_t self, int index){
    if(index >= 0 && index < self->amountPosts){
        printf("%s \\Reposts: %d\n", self->posts[index]->text, self->posts[index]->amountReposts);
        self->error = NO_ERROR;
    }
    else self->error = WRONG_INDEX;
}

void network_printNetwork(network_t self){
    for(int i = 0; i < self->amountPosts; i++){
        printf("%s \\Reposts: %d\n", self->posts[i]->text, self->posts[i]->amountReposts);
    }
}

void network_remove(network_t self){
    for(int i = 0; i < self->amountPosts; i++){
        free(self->posts[i]->text);
        free(self->posts[i]);
    }
    free(self);
}

void network_setNewTextForPost(network_t self, int index, const char * new_text){
    if(index >= 0 && index < self->amountPosts){
        if(strlen(new_text) > MAX_LENGTH_POST){
            self->error = WRONG_LENGTH_POST;
            } else {
                self->error = NO_ERROR;
                self->posts[index]->text = new_text;
            }
        } else self->error = WRONG_INDEX;
}

void network_setNewAmountRepostsForPost(network_t self, int index, int new_amountReposts){
    if(index >= 0 && index < self->amountPosts){
        if(new_amountReposts < 0){
            self->error = WRONG_AMOUNT_REPOSTS;
        } else {
            self->error = NO_ERROR;
            self->posts[index]->amountReposts = new_amountReposts;
        }
    } else  self->error = WRONG_INDEX;
}

int network_getPostWithMaxAmountReposts(network_t self){
    int maxReposts = self->posts[0]->amountReposts;
    int resultIndex = 0;
    for(int i = 1; i < self->amountPosts; i++){
        if(self->posts[i]->amountReposts > maxReposts){
            maxReposts = self->posts[i]->amountReposts;
            resultIndex = i;
        }
    }
    return resultIndex;
}

network_t network_getPostsWithRepostsMoreThanValue(network_t self, int value){
    if(value < 0){
        self->error = WRONG_AMOUNT_REPOSTS;
    } else {
        network_t new_network = network_create();
        for(int i = 0; i < self->amountPosts; i++){
            if(self->posts[i]->amountReposts > value){
                network_addNewPostToEnd(new_network, self->posts[i]->amountReposts, self->posts[i]->text);
            }
        }
        self->error = NO_ERROR;
        return new_network;
    }
}
ERROR_CODE network_getErrorStatus(network_t self){
    return self->error;
}

char * network_getTextOfPost(network_t self, int index){
    if(index >= 0 && index < self->amountPosts){
        self->error = NO_ERROR;
        return self->posts[index]->text;
    } else self->error = WRONG_INDEX;
}
