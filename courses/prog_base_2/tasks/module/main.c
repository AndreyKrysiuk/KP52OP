#include <stdio.h>
#include <stdlib.h>

#include "module.h"
int main(){

    network_t network = network_create();

    network_addPost(network,"Epolets perform in Minsk", 58);
    network_addPost(network,"Rammstein perform in Kiev in December 2016", 958);
    network_printPost(network);


    network_addPostByIndex(network, 1, "Oomph released a new video", 102);
    network_addPostByIndex(network, 0, "Three Days Grace concert in Kiev on January 29", 1500);
    network_printPost(network);


    network_deletePost(network, 2);
    network_addPostByIndex(network, 3, "Thousand Foot Krutch concert in Kiev on March 17", 187);
    network_addPostByIndex(network, 1, "Vasya from Zajopinsk concert in dvor tonigth", 1);
    network_printPost(network);

    printf("\nNumber of reposts of post %d is %d\n", 4, network_getAmountReposts(network, 4));
    printf("Number of posts in this network is %d\n",  network_getAmountPosts(network));
    printf("Max amount of reposts have post number %d\n", network_getMaxRepost(network));
    network_setNumOfRepost(network, 1, 0);
    network_printPost(network);


    printf("\nPosts with amount reposts more than 200");
    network_printPost(network_getPostsWithRepostsMoreThanArg(network, 200));

    network_remove(network);
    return 0;
}
