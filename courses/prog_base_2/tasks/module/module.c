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
    int amountPosts;
    post_t posts[MAX_AMOUNT_POSTS];
};

network_t network_create(){
    network_t new_network = malloc(sizeof(struct network_s));
    new_network->amountPosts = 0;
    return new_network;
}

void network_addNewPostToEnd(network_t self, int amountReposts, const char* text){
    self->posts[self->amountPosts] = malloc(sizeof(struct post_s));
    self->posts[self->amountPosts]->text = malloc(sizeof(char) * MAX_LENGTH_POST);
    self->posts[self->amountPosts]->amountReposts = amountReposts;
    self->posts[self->amountPosts]->text = text;
    self->amountPosts++;
}

void network_addNewPostByIndex(network_t self, int amountReposts, const char* text, int index){
    if(index >= 0 && index <= self->amountPosts){
        if(index == self->amountPosts){
            network_addNewPostToEnd(self, amountReposts, text);
        } else{
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
}

void network_removePostByIndex(network_t self, int index){
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
    }
}

int network_getAmountRepostsOfPost(network_t self, int index){
    if(index >= 0 && index < self->amountPosts)
        return self->posts[index]->amountReposts;
}

int network_getAmountPosts(network_t self){
    return self->amountPosts;
}

void network_printPost(network_t self, int index){
    if(index >= 0 && index < self->amountPosts)
        printf("%s \\Reposts: %d\n", self->posts[index]->text, self->posts[index]->amountReposts);
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
    if(index >= 0 && index < self->amountPosts)
        self->posts[index]->text = new_text;
}

void network_setNewAmountRepostsForPost(network_t self, int index, int new_amountReposts){
    if(index >= 0 && index < self->amountPosts)
        self->posts[index]->amountReposts = new_amountReposts;
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
    network_t new_network = network_create();
    for(int i = 0; i < self->amountPosts; i++){
        if(self->posts[i]->amountReposts > value){
            network_addNewPostToEnd(new_network, self->posts[i]->amountReposts, self->posts[i]->text);
        }
    }
    return new_network;
}
