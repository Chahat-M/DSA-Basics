#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Finding the most frequent element in the given array
// Time complexity - O(n)
// Space complexity - O(n)
void mostFreq(int arr[], int n){
    // Inserting every element in a hash table
    unordered_map<int, int> ump;
    for(int i = 0; i < n; i++)
        ump[arr[i]]++;
    
    // Finding max frequency
    int max_count = 0, result = -1;
    for(auto x : ump){
        if(max_count < x.second){
            max_count = x.second;
            result = x.first;
        }
    }

    cout << "Most frequnecy is of: " << result << endl;
}

// Finding if there exists a subarray with 0 sum
// Time complexity - O(n)
// Space complexity - O(n)
bool isZeroSum(int arr[], int n){
    unordered_set<int> us; // To store pre_sum 
    int pre_sum = 0;
    for(int i = 0; i < n; i++){
        pre_sum += arr[i];
        if(us.find(pre_sum) != us.end()) // If pre_sum is already existing
            return true; // Implies that somewhere in between the subarray sum is 0
        us.insert(pre_sum);
    }
    return false;
}

// Finding if there is a subarray with given sum
// Time complexity - O(n)
// Space complexity - O(n)
bool isSumX(int arr[], int n, int x){
    unordered_set<int> us;
    int pre_sum = 0;
    for(int i = 0; i < n; i++){
        pre_sum += arr[i];
        if(us.find(pre_sum - x) != us.end())
            return true;
        us.insert(pre_sum);
    }
}

// Largest binary subarray with equal no. of 0s and 1s
// Time Complexity - O(n)
// Space Complexity - O(n)
int binSubarray(int arr[], int n){
    unordered_map<int, int> ump;
    int max_len = 0, presum = 0;
    for(int i = 0; i < n; i++){
        arr[i] = (arr[i] == 0) ? -1 : 1;
        presum += arr[i];
        if(presum == 0)
            max_len = i + 1;
        if(ump.find(presum + n) != ump.end()){
            if(max_len < i - ump[presum + n])
                max_len = i - ump[presum + n];
        }
        else
            ump[presum + n] = i;
    }
    return max_len;
} 

// Finding if a pair with given sum exists in an unsorted array
// Time Complexity - 
// Space Complexity - 
bool isPair(int arr[], int n, int x){
    unordered_set<int> us;
    for(int i = 0; i < n; i++){
        if(us.find(x - arr[i]) != us.end())
            return true;
        us.insert(arr[i]);
    }
    return false;
}

int main(){
    int arr[12] = {1,1,1,1,0,0,1,1,1,1,0,0};
    cout << binSubarray(arr, 12);
    return 0;
}