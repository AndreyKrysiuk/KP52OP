#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*callback)(int, int *);

void underCB(int value, int * count){
     *count = *count + 1;
}
void overCB(int value, int * count){
     *count = *count + 1;
}
void underCB1(int value, int * count){
     *count = *count - 1;
}
void overCB1(int value, int * count){
     *count = *count - 1;
}
void check(int size, int arr[size], callback uCB, callback oCB, int k);

int main(void)
{
    callback cb1 = underCB;
    callback cb2 = overCB;
    srand(time(NULL));
    int size = 10;
    int size1 = 50;
    int k = 57;
    int k1 = 13;
    int arr[size];
    int arr1[size1];
    for(int i = 0; i < size; i++){
        arr[i] = rand()%100;
        printf("%d  ", arr[i]);
    }
    puts("");
    check(size, arr, cb1, cb2, k);
    for(int i = 0; i < size1; i++){
        arr1[i] = rand()%100;
        printf("%d  ", arr1[i]);
    }
    puts("");
    cb1 = underCB1;
    cb2 = overCB1;
    check(size1, arr1, cb1, cb2, k1);

}

void check(int size, int arr[size], callback uCB, callback oCB, int k){
    int countOCB = 0;
    int countUCB = 0;
    for(int i = 0; i < size; i++){
        if(arr[i] < k){
            if(uCB != NULL)
                uCB(arr[i], &countUCB);
        } else if(arr[i] >= k){
            if(oCB != NULL)
                oCB(arr[i], &countOCB);
        }
    }
    printf("Elements under %d: %d\n", k ,countUCB);
    printf("Elements over %d: %d\n", k ,countOCB);
}

