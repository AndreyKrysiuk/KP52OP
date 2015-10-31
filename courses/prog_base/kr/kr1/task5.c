#include<stdio.h>
#include<stdlib.h>

int main(){
    char str1[100] = "I've got a ticket to the moon, I'll be leaving here any day soon";
    char str2[100] = "they can't stop us let 'em try for heavy metal we will die";
    int arr[100];
    int i;
    for(i=0; i<100; i++){
    arr[i] = (str1[i]+str2[i])%127;
    printf("%i ", arr[i]);
    }

 return 0;
}
