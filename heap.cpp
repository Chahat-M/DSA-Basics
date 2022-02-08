// Binary heap is a complete binary tree stored in an array
#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

// Max heap - Complete binary tree; all descendants are smaller than the root
// Min heap - Complete binary tree; all descendants are greater than the root

// Implementing Min Heap
struct MinHeap{
    int *arr;
    int size;
    int capacity;
    
    MinHeap(int c){
        arr = new int[c];
        size = 0;
        capacity = c;
    }

    // Returns left child of the given index
    int left(int i){
        return 2 * i + 1;
    }

    // Returns right child of the given index
    int right(int i){
        return 2 * i + 2;
    }

    // Returns parent of the given index
    int parent(int i){
        return floor((i - 1 / 2));
    }

    // Inserting a new element to the node and even maintain minHeap properties after it
    void insert(int x){
        if(size == capacity)
            return;
        arr[size] = x;
        size++;
        for(int i = size - 1; i != 0 && arr[parent(i)] > arr[i]; ){
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Heapify - only one node is wrong to dissatisfy minHeap property
    // Makes the binary heap a proper minHeap
    // Time complexity - O(h) ~ O(logn), but h for complete binary tree = log n
    // Auxiliary space - O(h)
    void minHeapify(int i){
        int lt = left(i);
        int rt = right(i);
        int minimum = i;
        if(lt < size && arr[i] > arr[lt]){
            minimum = lt;
        }
        if(rt < size && arr[i] > arr[minimum])
            minimum = rt;
        if(minimum != i){
            swap(arr[i], arr[minimum]);
            minHeapify(minimum);
        }
    }

    // Get minimum of the binary heap
    int getMin(){
        return arr[0];
    }

    // Remove minimum from the min heap such that the remaining binary heap is also a min Heap
    // Returns the minimum element
    /* Approach - swap the root with the last element and remove last element
                - make the remaining heap a minHeap
    Time complexity - O(logn)
    Auxiliary space - depends upon minHeapify
    */
    int extractMin(){
        if(size == 0)
            return INT16_MAX;
        if(size == 1){
            size--;
            return arr[0];
        }
        swap(arr[0], arr[size - 1]);
        size--; // Removing the last element
        minHeapify(0);
        return arr[size];
    }

    // Decrease operation - maintain the heap even after decreasing
    // Time complexity - O(logn)
    void decreaseKey(int i, int x){
        arr[i] = x; // Updating the value to the given value at the specified index
        while(i != 0 && arr[parent(i)] > arr[i]){
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Delete operation - should follow minHeap property even after deleting
    // Time complexity - O(logn) 
    void deleteKey(int i){
        decreaseKey(i, INT16_MIN);  // Makes the desired key as root - O(logn)
        extractMin();  // Removes the minimum(root) and balances minHeap - O(logn)
    }  

    // Building a minheap from a given random array - imp
    /* Approach - Make the parent of last element (node) as a proper minHeap
    Time complexity - O(n), check video for detialed explaination
    */
    void buildMinHeap(){  // No parameters, so use insert() for adding elements to heap and then call it
        int start = (size - 1) - 1 / 2; // parent of last element
        for(int i = start; i >= 0; i--)
            minHeapify(i);  // Bottom to top approach
    }
    //***************************************************************************************************************************************
    // Overriding buildMinHeap() and minHeapify() for later uses

    void buildMinHeap(int arr[], int n){
        int start = (n - 1) - 1 / 2;
        for(int i = start; i >= 0; i--)
            minHeapify(arr, n, i);
    }

    void minHeapify(int arr[], int n, int i){
        int lt = 2 * i + 1;
        int rt = 2 * i + 2;
        int minimum = i;
        if(lt < n && arr[lt] < arr[minimum])
            minimum = lt;
        if(rt < n && arr[rt] < arr[minimum])
            minimum = rt;
        if(minimum != i){
            swap(arr[minimum], arr[i]);
            minHeapify(arr, n, minimum);
        }
    }
    //****************************************************************************************************************************************
    
    // Same as minHeapify(), but creates a maxHeap
    // Why extra parameters - will be used for sorting heap
    //                      - bcoz of this it can be called for an array directly, without inserting the elements of the array to the heap using insert()
    void maxHeapify(int arr[], int n, int i){
        int lt = left(i);
        int rt = right(i);
        int maximum = i;
        if(lt < n && arr[maximum] < arr[lt])
            maximum = lt;
        if(rt < n && arr[maximum] < arr[rt])
            maximum = rt;
        if(maximum != i){
            swap(arr[i], arr[maximum]);
            maxHeapify(arr, n, maximum);
        }
    }

    // Same as buildMinHeap(), but builds a maxHeap
    // Additional parameters help to call directly for an array
    void buildMaxHeap(int arr[], int n){
        int start = (n - 1) - 1 / 2;
        for(int i = start; i >= 0; i--)
            maxHeapify(arr, n, i);
    }

    // Heap sort
    /* Approach - Using selection sort - O(n^2), but instead of linear traversal of array using maxHeap
                - Converts the random formed heap to MaxHeap
                - Repeatedly swapping root(first element) with last node
                - Change the new formed heap to maxHeap 
    Note - Use maxHeap for ascending order
         - Use minHeap for descending order in the same algorithm
    Time complexity - O(nlogn)
    */
    void sortHeap(int arr[], int n){
        buildMaxHeap(arr, n); // Initially the array is in descending order
        for(int i = n - 1; i > 0; i--){
            swap(arr[i], arr[0]);
            // Keep the last element fixed and modify the remaining heap
            maxHeapify(arr, i, 0); // Bcoz of the extra parameters the array remians same and limited heap is modified 
        }
    }

    // Sort a K-sorted array - imp
    // An element at i index in sorted array will be present between i-k to i+k in unsorted array
    // Time complexity - O(n + klogk)
    void sortK(int arr[], int n, int k){
        priority_queue<int, vector<int>, greater<int>> pq;  // Declaring a minHeap
        
        // Maintaining minHeap for k elements
        for(int i = 0; i <= k; i++)   // O(klogk)
            pq.push(arr[i]);
        int index = 0;  // Variable for where to put next element in sorted array

        for(int i = k + 1; i < n; i++){  // O(n - klogk)
            arr[index++] = pq.top();    // The indexth element of sorted array = root of minHeap, Incrementing the index at the same time
            pq.pop();   // Removing the inserted element from the heap
            pq.push(arr[i]);    // Inserting the next element in the heap and rearranging it as minHeap
        }
        
        while(pq.empty() == false){   // O(klogk)
            arr[index++] = pq.top();
            pq.pop();
        }
    }

    // Purchase max items from a given sum
    // Can be done using sorting also
    // Time complexity - O(n) + O(res * logn)
    int maxItems(int cost[], int n, int sum){
        priority_queue<int,vector<int>,greater<int>> pq;  // Forming a duplicate heap 
        int res = 0;
        for(int i = 0; i < n; i++)  // O(n)
            pq.push(cost[i]);

        while(pq.top() <= sum){ // O(res * logn)
            sum -= pq.top();
            pq.pop();
            res++;
        }
        return res;
    }

    // K largest elements of an unsorted array
    //-----------------------------------------------------------------------------------------
    /* Approach 1 - Sort the heap, and then print k elements (ascending order)
    Time complexity - O(nlogn + k)
    */
    void kLargest1(int arr[], int n, int k){
        sortHeap(arr, n); //O(nlogn)
        for(int i = k; i > 0; i--) //O(k)
            cout << arr[n - i] << " ";
    }

    /* Approach 2 - In the original sorting algorithm, sort upto k elements only and then print it (descending order)
    Time complexity - O(n + klogn)
    */
    void kLargest2(int arr[], int n, int k){
        buildMaxHeap(arr, n); // O(n)
        for(int i = n - 1; i >= 0; i--){    // O(klogn)
            if(k == 0)
                break;
            swap(arr[i], arr[0]);
            cout << arr[i] << " ";
            k--;
            maxHeapify(arr, i, 0); 
        } 
    }

    /* Approach 3 - Build minHeap for first k items
                  - If root is smaller than current element, replace
                  - Then Print (ascending order) 
    Time complexity - O(n + (n-k)*logk)
    */
    void kLargest3(int arr[], int n, int k){
        priority_queue<int, vector<int>, greater<int>> pq;
        for(int i = 0; i < k; i++)  // O(k)
            pq.push(arr[i]);

        for(int i = k; i < n; i++){ // O((n-k)*logk)
            if(arr[i] > pq.top()){
                pq.pop();
                pq.push(arr[i]);
            }
        }

        while(pq.empty() == false){ // O(k)
            cout << pq.top() << " ";
            pq.pop();
        }
    }
    //----------------------------------------------------------------------------------------------------------------

    // K Closest elements of a given no
    void kClosest(int arr[], int n, int k, int x){
        
    }

};



int main(){
    MinHeap mh(5);
    int arr[5] = {5, 15, 10, 20, 8};
    mh.kLargest1(arr, 5, 3);
    return 0;
}