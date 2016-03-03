#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct post_s* post_t;
typedef struct network_s* network_t;

network_t network_create();
network_t network_getPostsWithRepostsMoreThanArg(network_t self, int amountRepost);

int network_getAmountReposts(network_t self, int index);
int network_getAmountPosts(network_t self);
int network_getMaxRepost(network_t self);

void network_deletePost(network_t self, int index);
void network_addPost(network_t self, char * text, int amountReposts);
void network_addPostByIndex(network_t self, int index, char* text, int amountReposts);
void network_printPost(network_t self);
void network_remove(network_t self);
void network_setNumOfRepost(network_t self, int index, int amountReposts);

char* network_getPostByIndex(network_t self, int index);





#endif // MODULE_H_INCLUDED
