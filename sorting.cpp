#include <iostream>
using namespace std;

// Merge two sorted arrays
void merge(int arr1[], int arr2[], int num1, int num2){
    int i = 0;
    int j = 0;
    while(i < num1 && j < num2){
        if(arr1[i] < arr2[j] ){
            cout << arr1[i] << " ";
            i++;
        }

        else if(arr1[i] > arr2[j]){
            cout << arr2[j] << " ";
            j++;
        }

        else {
            cout << arr1[i] << " " << arr2[j] << " ";
            i++;
            j++;
        }
    }
    while(i < num1){
        cout << arr1[i] << " ";
        i++;
    }
    while(j < num2){
        cout << arr2[j] << " ";
        j++;
    }
}

int main(){
    int arr1[5] = {2,3,6,7,10};
    int arr2[3] = {4,10,20};
    merge(arr1, arr2, 5, 3);
}
