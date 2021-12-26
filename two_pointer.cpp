#include <iostream>
using namespace std;

// A sorted array is given, determine the given sum exists or not
// For sorted array, O(n) - best method
// For unsorted array, use hashing

bool pair_check(int arr[], int n, int sum){
    int left = 0, right = n-1;
    for(int i = 0; i < n; i++){
        if(left == right)
            return false;
        if(arr[left] + arr[right] == sum)
            return true;
        else if(arr[left] + arr[right] > sum)
            right--;
        else
            left++;
    }
    return false;
}

// To check if their is a triplet with given sum in the given sorted array

bool isPair(int arr[], int left, int right, int sum){
    while(left < right){
        if(arr[left] + arr[right] == sum)
            return true;
        else if(arr[left] + arr[right] > sum)
            right--;
        else
            left++;
    }
    return false;
}

bool triplet(int arr[], int n, int sum){
    for(int i = 0; i < n; i++){
        if(isPair(arr, i+1, n-1, sum - arr[i]))
            return 1;
        else return false;
    }
    return false;
}



int main(){
    int n = 7;
    int arr[n] = {2,5,7,8,19,20,30};
    int sum = 52;
    cout<<triplet(arr,n,sum);
}