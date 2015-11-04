#include<stdio.h>
#include<stdlib.h>

void fillRand1(int arr[], int size)
{
    int i;
    for(i=0; i < size; i++){
        arr[i]=rand()%99 + 1;
    }
}

int checkRand1(int arr[], int size){
    int i;
    int check = 1;
    for(i=0; i<size; i++){
        if(arr[i]<1&&arr[i]>99){
        check=0;
        }
    }
    return check;
}

float meanValue(int arr[], int size){
    int i;
    float sum = 0;
    float mean;
    for(i=0; i<size; i++){
        sum += arr[i];
    }
    mean = sum/size;
    return mean;
}

int minValue(int arr[], int size){
int i;
int min = arr[0];
for(i=1; i<size; i++){
    if(arr[i]<min){
        min = arr[i];
    }
}
return min;
}

int meanIndex(int arr[], int size){
int i;
float dif;
float mean = meanValue(arr,size);
int meanIndex = 0;
dif = abs(mean-arr[0]);
for(i=1; i<size; i++){
    if((dif>abs(mean - arr[i]))&&((mean - arr[i] != 0))){
        dif = abs(mean - arr[i]);
        meanIndex = i;
    }
}
return meanIndex;
}

int minIndex(int arr[], int size){
    int i;
    int minIndex;
    for(i=0; i<size; i++){
        if(arr[i]==minValue(arr,size)){
            minIndex = i;
            break;
        }
    }
    return minIndex;
}

int maxOccurance(int arr[], int size){
    int i,j;
    int maxoccurance;
    int count=0;
    int countNum[999]={0};
    int countNumMax = 0;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            if(arr[i]==arr[j]) {
               count++;
            }
        }
        countNum[i] = count;
        count = 0;
    }
        for(i=0;i<size;i++){
            if(countNum[i]>countNumMax){
                countNumMax = countNum[i];
                maxoccurance=arr[i];
            }
             else if(countNum[i]==countNumMax && arr[i]>maxoccurance) {
               maxoccurance = arr[i];
             }
       }
     return maxoccurance;
}

int diff(int arr1[], int arr2[], int res[], int size){
    int i;
    int checkDiff=1;
    for(i=0;i<size;i++){
        res[i]=arr1[i]-arr2[i];
        if(res[i]!=0){
            checkDiff = 0;
        }
    }
return checkDiff;
}

void mult(int arr1[], int arr2[], int res[], int size){
 int i;
 for(i=0;i<size;i++){
    res[i]=arr1[i]*arr2[i];
    }
 }

int lt(int arr1[], int arr2[], int size){
    int i;
    int check = 1;
    for(i=0;i<size;i++){
            if(arr1[i]>=arr2[i]){
                check = 0;
            }
    }
return check;
}

void land(int arr1[], int arr2[], int res[], int size)
{
    int i;
    for(i=0;i<size;i++){
        res[i] = arr1[i]&&arr2[i];
    }
}



