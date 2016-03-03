#include "module.h"

#define MAX_AMOUNT_POST 50
#define MAX_LENGTH_POST 100

struct network_s{
   post_t posts[MAX_AMOUNT_POST];
    int amountPost;
};

struct post_s{
    char * text;
    int amountReposts;
};

network_t network_create(){
    network_t net = (network_t)malloc(sizeof(struct network_s));
    net->amountPost = 0;
    return net;
}

int network_getAmountReposts(network_t self, int index){
    if(index > network_getAmountPosts(self)){
        return -1;
    }
    return self->posts[index]->amountReposts;
}
void network_deletePost(network_t self, int index){
    for(int i = index + 1;  i < self->amountPost; i++){
        strcpy(self->posts[i - 1]->text, self->posts[i]->text);
        self->posts[i - 1]->amountReposts = self->posts[i]->amountReposts;
    }
    free(self->posts[self->amountPost - 1]->text);
    free(self->posts[self->amountPost - 1]);
    self->amountPost--;
}
void network_addPost(network_t self, char * text, int amountReposts){
    self->posts[self->amountPost] = (post_t)malloc(sizeof(struct post_s));
    self->posts[self->amountPost]->text = (char*)malloc(MAX_LENGTH_POST * sizeof(char));
    self->posts[self->amountPost]->amountReposts = amountReposts;
    strcpy(self->posts[self->amountPost]->text,text);
    self->amountPost++;
}
void network_addPostByIndex(network_t self, int index, char* text, int amountReposts){
    self->posts[self->amountPost] = (post_t)malloc(sizeof(struct post_s));
    self->posts[self->amountPost++]->text = (char*)malloc(MAX_LENGTH_POST * sizeof(char));
    for (int i = self->amountPost - 1; i >= index + 1; i--){
        strcpy(self->posts[i]->text, self->posts[i - 1]->text);
        self->posts[i]->amountReposts = self->posts[i - 1]->amountReposts;
    }
    strcpy(self->posts[index]->text,text);
    self->posts[index]->amountReposts = amountReposts;
}
int network_getMaxRepost(network_t self){
    int max = network_getAmountReposts(self, 0);
    int index = 0;
    for(int i = 1; i < self->amountPost; i++){
        if(network_getAmountReposts(self,i) > max){
            max = network_getAmountReposts(self,i);
            index = i;
        }
    }
    return index;
}

void network_setNumOfRepost(network_t self, int index, int amountReposts){
   self->posts[index]->amountReposts = amountReposts;
}

char* network_getPostByIndex(network_t self, int index){
    if(index > network_getAmountPosts(self)){
        return -1;
    }
    return self->posts[index]->text ;
}

network_t network_getPostsWithRepostsMoreThanArg(network_t self, int amountRepost){
    network_t resultListOfPosts = network_create();
    for(int i = 0; i < self->amountPost; i++){
        if(self->posts[i]->amountReposts > amountRepost){
            network_addPost(resultListOfPosts, self->posts[i]->text, self->posts[i]->amountReposts);
            resultListOfPosts->posts[resultListOfPosts->amountPost - 1]->amountReposts = self->posts[i]->amountReposts;
        }
    }
    return resultListOfPosts;
}

int network_getAmountPosts(network_t self){
    return self->amountPost;
}

void network_remove(network_t self){
    for (int i = 0; i< self->amountPost; i++){
        free(self->posts[i]->text);
    }
    for (int i = 0; i< self->amountPost; i++){
        free(self->posts[i]);
    }
    free(self);
}

void network_printPost(network_t self){
    int i;
    puts("");
    for(i = 0; i < network_getAmountPosts(self); i++)
    printf("%s  Reposts: %d\n", self->posts[i]->text, self->posts[i]->amountReposts);
}

