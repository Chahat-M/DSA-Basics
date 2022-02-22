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

    // K Closest elements of a given no in an array
    void kClosest(int arr[], int n, int k, int x){
        priority_queue<pair<int,int>> pq;
        for(int i = 0; i < k; i++)
            pq.push({abs(arr[i] - x), i});

        for(int i = k; i < n; i++){
            if(abs(arr[i] - x) < pq.top().first){
                pq.pop();
                pq.push({abs(arr[i] - x), i});
            }
        }

        while(pq.empty() == false){
            cout << arr[pq.top().second] << " ";
            pq.pop();
        }
    }

    // Merge K sorted arrays and make the resulting array sorted
    //--------------------------------------------------------------------------------------------------------------
    /* Method 1 - Super Naive Approach
    Approach - Join all the arrays and then sort
    Time complexity - O(nk * lognk)
    */

    /* Method 2 - Naive Approach
    Approach - Copy 1st array in the resulting array
             - Merge the other arrays one by one with the resulting array
             - Merging = Join the two arrays s.t they are sorted
    Time complexity - O(n * k^2), n = max size of array, k = numbers of array
    */
    // To merge 2 arrays
    vector<int> mergeArrays(vector<int> arr1, vector<int> arr2){
        int i = 0, j = 0;
        vector<int> res; // The merged array

        while(i < arr1.size() && j < arr2.size()){
            if(arr1[i] < arr2[j])
                res.push_back(arr1[i++]);  // Inserting the smaller element in the merged array and updating the variable simultaneously
            else
                res.push_back(arr2[j++]);
        }

        while(i < arr1.size()){ // Elements left in arr1
            res.push_back(arr1[i++]);
        }

        while(j < arr2.size()){ // Elements left in arr2
            res.push_back(arr2[j++]);
        }

        return res;
    }

    // To merge K arrays
    vector<int> mergeKArrays2(vector<vector<int>> vect){
        vector<int> result = vect[0]; // Copying the 1st array to the resulting array

        for(int i = 1; i < vect.size(); i++){
            result = mergeArrays(result, vect[i]); // Merging the resulting array with the next array
        }
        return result;
    }

    /* Method 3 - Efficient way - imp
    Approach - Create minHeap of first elements of all the arrays
             - Extract min and add it to the resulting array
             - At the same time, insert the next element of same array and then repeat from 2
    Time complexity -  
    */
    // Since, we need Tripletrmation about the array to which the element belongs 
    // We store it as an object which contains all the values
    struct Triplet{
        int value, array_pos, value_pos;
        Triplet(int val, int ap, int vp){
            value = val; // The value of the element
            array_pos = ap; // The position of array in all arrays to which the element belongs
            value_pos = vp; // The position of the element in that particular array
        }
    };

    struct Compare{ // To make the priority queue of ascending order
        bool operator()(Triplet &t1, Triplet &t2){
            return t1.value > t2.value;
        }
    };

    vector<int> mergeKArrays3(vector<vector<int>> vect){
        vector<int> result;
        priority_queue<Triplet, vector<Triplet>, Compare> pq; // Creating minHeap

        // Adding 1st element of all arrays
        for(int i = 0; i < vect.size(); i++){
            Triplet t(vect[i][0], i, 0);
            pq.push(t);
        }

        while(!pq.empty()){
            Triplet curr = pq.top();
            pq.pop();
            result.push_back(curr.value);
            int ap = curr.array_pos;
            int vp = curr.value_pos;
            if(vp + 1 < vect[ap].size()){ // If next element exists in the same array
                Triplet trp(vect[ap][vp + 1], ap, vp + 1);
                pq.push(trp);
            }
        }

        return result;
    }
    //-----------------------------------------------------------------------------------------------------------------

    // Median of a stream
    /* Efficient solution
    Approach - Maintain two containers, keep smaller elements in one and greater in other
             - Left container - maxHeap, right container - minHeap
             - In case of even elements, median = (max of maxHeap + min of minHeap) / 2
             - In case of odd elements, median = max of maxHeap
             - Here, we will be maintaining extra elements in left only
    Time complexity - O(nlogn)
    */
    void printMedian(int arr[], int n){
        priority_queue<int> left;   // maxHeap
        priority_queue<int, vector<int>, greater<int>> right;   // minHeap

        left.push(arr[0]);
        cout << arr[0] << " ";
        for(int i = 1; i < n; i++){
            int x = arr[i];
            if(left.size() > right.size()){ // Extra elements on left = odd no. of elements initially 
                if(left.top() > x){
                    right.push(left.top());
                    left.pop();
                    left.push(x); // new element added - size increased by 1 = even
                }
                else
                    right.push(x);
                cout << (left.top() + right.top()) / 2.0 << " ";
            }
            else{   // Equal elements with both - even
                if(left.top() >= x){
                    left.push(x); // Extra element to be maintained in left always - our choice
                }
                else{
                    right.push(x);
                    left.push(right.top());
                    right.pop();
                }
                cout << left.top() << " ";  // After adding an element even->odd
            }
        }
    }
};

int main(){
    MinHeap mh(5);
    vector<vector<int>> arr{ { 10, 20, 30 }, { 5, 15 }, { 1, 9, 11, 18 } };
    vector<int> res = mh.mergeKArrays2(arr);
    cout << "Merged array is " << endl; 
    for (auto x : res) 
        cout << x << " ";
    return 0;
}