// Advantage of BST - Reduces time complexity of basic operations
//                  - Like search, insert, delete, sorted traversal 

#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <map>
#include <queue>
using namespace std;

struct Node{
    int data;
    Node *left;
    Node *right;

    Node(int x){
        data = x;
        left = right = NULL;
    }
};

// Search a given node in BST
//----------------------------------------------------------------------------------------------
// Method 1 - Recursive approach
// Time complexity - O(h)
// Auxiliary space - O(h)
bool searchRec(Node *root, int x){
    if(root == NULL)
        return false;
    else if(root->data == x)
        return true;
    else if(root->data > x)
        return searchRec(root->left, x);
    else
        return searchRec(root->right, x);
}

// Method 2 - Iterative approach
// Time complexity - O(h)
// Auxiliary space - O(1)
bool searchIt(Node *root, int x){
    while(root != NULL){
        if(root->data == x)
            return true;
        else if(root->data > x)
            root = root->left;
        else
            root = root->right;   
    }
    return false;
}
//------------------------------------------------------------------------------------------

// Insert in a BST
//--------------------------------------------------------------------------------------------
// Method 1 - Recursive approach
// Time complexity - O(h)
// Auxiliary space - O(h)
Node *insertRec(Node *root, int x){
    if(root == NULL)
        return new Node(x);
    else if(root->data > x)
        root->left = insertRec(root->left, x);
    else
        root->right = insertRec(root->right, x);  
    return root;   
}

// Method 2 - Iterative approach
// Time complexity - O(h)
// Auxiliary space - O(1)
Node *insertIt(Node *root, int x){
    Node *temp = new Node(x);
    Node *parent = NULL, *curr = root;
    while(curr != NULL){
        parent = curr;
        if(curr->data == x)
            return root;
        if(curr->data > x)
            curr = curr->left;
        else 
            curr = curr->right;
    }
    if(parent == NULL) // When tree is empty
        return temp;
    if(parent->data > x)
        parent->left = temp;
    else
        parent->right = temp;
    
}
//------------------------------------------------------------------------------------------

// Delete the given node in BST - imp
// NOTE - Even after deleting, BST should maintain its property
/* Approach -
For a node that has both left and right child, deletion is tricky
Need to replace that node either by its next greater node or smaller node
Here, we get the next greater node = next element (of the given element) in inorder traversal 
*/

// To get next greater element = leftmost child of right child of the given root
// Doesn't applicable in general case as right child may not exist
Node *getSuccessor(Node *root){
    root = root->right;
    while(root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

// Time complexity - O(h)
// Auxiliary space - O(h)
Node *deleteNode(Node *root, int x){
    if(root == NULL)
        return root;
    if(root->data > x){
        root->left = deleteNode(root->left, x);
    }
    else if(root->data < x)
        root->right = deleteNode(root->right, x);
    else{
        if(root->left == NULL){
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if(root->right == NULL){
            Node *temp = root->left;
            delete root;
            return temp;
        }
        else{ // Imp part
            // Instead of deleting the req node, copy successor's value to it and then delete successor
            // Why so -> deleting successor requires less work as it will be a leaf node
            Node *temp = getSuccessor(root);
            root->data = temp->data;  // = deleting the root node
            // Why right -> successor node is from right subtree
            root->right = deleteNode(root->right, temp->data);  // Calling for right subtree, and searching the successor to delete
        }
    }
    return root;
}

// Floor of given value in BST
// = Largest value that is smaller than the given value
// Time complexity - O(h)
// Auxiliary space - O(1)
Node *floorNode(Node *root, int x){
    Node *parent = root;
    while(root != NULL){
        if(x == root->data)
            return root;
        else if(x < root->data)
            root = root->left;
        else{
            parent = root;
            root = root->right;
        }
    }
    return parent;
}

// Ceil of the given value in BST
// = smallest of all the larger value than the given
// Time complexity = O(h)
// Auxiliary space -O(1)
Node *ceilNode(Node *root, int x){
    Node *parent = NULL;
    while(root != NULL){
        if(x == root->data)
            return root;
        else if(root->data < x)
            root = root->right;
        else{
            parent = root;
            root = root->left;
        }
    }
    return parent;
}

// AVL Trees - One Kind of Self balancing BST
/* 
Insertion, Deletion on AVL tree can unbalance it, so need to perform some rotations to balance it again
Search on AVL tree is same as search on a BST
Balance factor = abs( height(left subtree) - height(right subtree) ) <= 1 (0 ,1)
If balance factor > 1, rotations require to balance
*/

// Red Black tree - Other kind of self balancing BST
/*
Every node is either black or red
Root is always black
No 2 consecutive Reds
No. of black nodes from root to leaf is same for all 
*/

// Ceiling on left side of all elements of an array
// Time complexity - O(nlogn)
// Auxiliary space - O(n)
void printCeiling(int arr[], int n){
    cout << -1 << " ";  // For first element, no ceiling
    set<int> s; // Sorted self balancing BST
    s.insert(arr[0]);
    for(int i = 1; i < n; i++){
        if(s.lower_bound(arr[i]) != s.end())    // s.lower_bound(value) returns iterator to the next element 
            cout << (* s.lower_bound(arr[i]) ) << " ";  // So dereferncing is required
        else
            cout << -1 << " ";
        s.insert(arr[i]);      // O(logn)
    }
}

// Print floor on left side of all elements of an array
// Time complexity - O(nlogn)
// Auxiliary space - O(n)
void printFloor(int arr[], int n){
    cout << -1 << " ";  // For first element, no floor
    set<int, greater<int>> s;   // greater<int> makes the set store value in decreasing order
    s.insert(arr[0]);
    for(int i = 1; i < n; i++){
        s.lower_bound(arr[i]) != s.end() ? cout << (* s.lower_bound(arr[i])) << " " : cout << -1 << " ";
        s.insert(arr[i]);
    }
}

// Find Kth smallest in BST by creating a data structure - imp
//------------------------------------------------------------------------------------------------
// Naive approach
// Time complexity - O(h + k)
void printKth(Node *root, int k){
    static int count = 0;
    if(root != NULL){
        printKth(root->left, k);
        count++;
        if(count == k){
            cout << root->data;
            return;
        }
        printKth(root->right, k);
    }
}

// Efficient solution
// By modifying the node structure of BST
// Time complexity - O(h)
struct NodeKth{
    int data;
    NodeKth *left, *right;
    // Modification -
    int lcount; // To count no. of nodes in left subtree 

    NodeKth(int x){
        data = x;
        left = right = NULL;
        lcount = 0;
    }
};

NodeKth *insert(NodeKth *root, int x);  // insert() for new structure 

void printKthEff(NodeKth *root, int k){
    int count = root->lcount + 1; // Default is 0
    if(count == k)
        cout << root->data;
    else if(count > k)
        printKthEff(root->left, k);
    else
        printKthEff(root->right, k - count);
}

NodeKth *insert(NodeKth *root, int x){
    if(root == NULL)
        return new NodeKth(x);
    if(root->data > x){
        root->left = insert(root->left, x);
        root->lcount++; // Providing lcount - no. of left subtree
    }
    else if(root->data < x)
        root->right = insert(root->right, x);   // lcount not updated bcoz right subtree nodes aren't counted
    return root;  
}
//----------------------------------------------------------------------------------------------------------------------------------

// Check for BST - if a binary tree is a BST or not - imp
//----------------------------------------------------------------------------------------------------------------------------------
/* Wrong approach - Traversing every node, and its left should be smaller and right should be greater
                  - Example ->
                  - There can be a node in left of parent node in right subtree which is smaller than the root of the tree
*/

// Correct but inefficient method
/* Approach - The maximum in left subtree < root
            - And the minimum in right subtree > root -> (whole right subtree is >)
Time complexity - O(n^2)
*/
int maxValue(Node *root){
    if(root == NULL)
        return INT16_MIN;
    int maximum = root->data;
    int lmax = maxValue(root->left);
    int rmax = maxValue(root->right);
    maximum = max(max(lmax, rmax), maximum);
    return maximum;
}

int minValue(Node *root){
    if(root == NULL)
        return INT16_MAX;
    int minimum = root->data;
    int lmin = minValue(root->left);
    int rmin = minValue(root->right);
    minimum = min(min(lmin, rmin), minimum);
    return minimum;
}

bool checkBST1(Node *root){
    if(root == NULL)
        return true;
    if(root->right != NULL && minValue(root->right) < root->data)
        return false;
    if(root->left != NULL && maxValue(root->left) < root->data)
        return false;
    if(checkBST1(root->left) == false || checkBST1(root->right) == false)
        return false;
    return true;
}

// Correct and efficient method
/* Approach - For every node specify a range between which it should lie
Time complexity - O(n)
*/
bool checkBST2(Node *root, int lmax, int rmin){ 
    // Default value of lmax = INT8_MIN, rmin = INT8_MAX
    if(root == NULL)
        return true;
    // Value of root > max of left subtree
    // Value of root < min of right subtree
    // For root's left node - upper range changes to root's value
    // For root's right node - lower range changes to root's value 
    return(root->data > lmax && root->data < rmin && checkBST2(root->left, lmax, root->data) && checkBST2(root->right, root->data, rmin));
}

// Efficent solution
/* Approach - If it's BST, inorder traversal will be sorted 
Time complexity - O(n)
Auxiliary space - O(n), if auxiliary array is used to store the inorder traversal
                - O(h), without auxiliary array, by maintaining a variable to store the value of last visited node 
*/
bool checkBST3(Node *root){
    static int prev = INT16_MIN;
    if(root == NULL)
        return true;
    if(checkBST3(root->left) == false)
        return false;
    if(prev >= root->data)
        return false;
    prev = root->data;
    return checkBST3(root->right);
}
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

// Fix BST with two nodes swapped - only by swapping two nodes the BST will be fixed
// Returns the two nodes that need to be swapped
// Time complexity - O(n)
Node *fprev = NULL, *fval1 = NULL, *fval2 = NULL; 
void fixBST(Node *root){
    if(root == NULL)
        return;
    fixBST(root->left);
    if(fprev != NULL && root->data < fprev->data){
        if(fval1 == NULL)
            fval1 = fprev;
        fval2 = root;
    }
    fprev = root;
    fixBST(root->right);
}

// Pair sum in BST - if there is any pair that sums to the given number
//----------------------------------------------------------------------------------------------------------------
/* Method 1 
Inorder traversal and two pointer approach
Time complexity - O(n)
Auxiliary space - O(n)
*/
bool pairSum1(Node *root, int sum, vector<int> &vect){
    if(root == NULL)
        return false;
    pairSum1(root->left, sum, vect);
    vect.push_back(root->data);
    pairSum1(root->right, sum, vect);
    int first = 0, second = vect.size() - 1;
    for(int i = 0; i < vect.size(); i++){
        if(first == second)
            return false;
        if(vect[first] + vect[second] == sum)
            return true;
        else if(vect[first] + vect[second] > sum)
            second--;
        else
            first++;
    }
    return false;
}

/* Method 2
Using hsing, can be done using set also, but hashing works for normal binary tree as well
Time complexity - O(n) , but once found returns, doesn't travel the whole tree
Auxiliary space - O(n)
*/
bool pairSum2(Node *root, int sum, unordered_set<int> &hs){
    if(root == NULL)
        return false;
    if(pairSum2(root->left, sum, hs) == true)
        return true;
    if(hs.find(sum - root->data) != hs.end())
        return true;
    else
        hs.insert(root->data);
    return pairSum2(root->right, sum, hs);
}
//---------------------------------------------------------------------------------------------------------------------------------------

// Vertical sum in a Binary tree - imp
/* Approach - Store the {horizontal distance, value of node} in map
            - Create two functions - to store the values in the map, to access the map
Time complexity - O(nlog(hdist) + hdist) ~ O(nlog(hdist))
*/
void createSumMap(Node *root, int hdist, map<int, int> &mp){    //O(nlog(hdist))
    if(root == NULL)
        return;
    createSumMap(root->left, hdist - 1, mp);
    // hdist = horizontal distance from root of the main tree
    mp[hdist] += root->data; // If key not present, creates one with value 0
    createSumMap(root->right, hdist + 1, mp);
}

// Main wrapper function
void verticalSum(Node *root){   //O(hdist)
    map<int, int> mp;
    createSumMap(root, 0, mp);
    for(auto sum : mp)  // auto in replacement of map<int, int>::iterator sum
        cout << sum.second << " ";
}

// Vertical traversal of a binary tree - imp
/* Approach - Since duplicate values can't be stored in map, maintain an array to store all the nodes with same hdist
            - Follow level order traversal as the node which is first vertically has to be printed first
// Time complexity - 
*/
void VTraversal(Node *root){
    if(root == NULL)
        return;
    map<int, vector<int>> mp;   // Store unique hdist and its corresponding all nodes
    queue<pair<Node *, int>> q;
    q.push( {root, 0} );
    while(q.empty() == false){
        auto p = q.front(); // Getting first pair from the queue
        Node *curr = p.first; // Getting first element = node of the tree from the pair
        int hdist = p.second;
        mp[hdist].push_back(curr->data);    // Storing the array of nodes with same hdist
        q.pop();
        if(curr->left != NULL)
            q.push( {curr->left, hdist - 1} );    // Pushing pair
        if(curr->right != NULL)
            q.push( {curr->right, hdist + 1} );
    }
    // Printing the nodes
    for(auto it : mp){
        vector<int> vect = it.second;
        for(int x : vect)
            cout << x << " ";
        cout << '\n';
    }
}

// Top view of Binary tree = first element of the vertical line
void TopView(Node *root){
    if(root == NULL)
        return;
    map<int, int> mp;
    queue<pair<Node *, int>> q; // For level order traversal
    q.push( {root, 0} );
    while(q.empty() == false){
        auto p = q.front();
        Node *curr = p.first;
        int val = curr->data;
        int hdist = p.second;
        q.pop();
        if(mp.find(hdist) == mp.end())
            mp[hdist] = val;
        if(curr->left != NULL)
            q.push( {curr->left, hdist - 1} );
        if(curr->right != NULL)
            q.push( {curr->right, hdist + 1} );
    }
    for(auto it : mp)
        cout << it.second << " ";
}

// Bottom view of Binary tree
void BottomView(Node *root){
    if(root == NULL)
        return;
    map<int, int> mp;
    queue<pair<Node *, int>> q; // For level order traversal
    q.push( {root, 0} );
    while(q.empty() == false){
        auto p = q.front();
        Node *curr = p.first;
        int val = curr->data;
        int hdist = p.second;
        q.pop();
        // The only different line from TopView() code
        mp[hdist] = val;    // Keeps on updating value for the same key
        if(curr->left != NULL)
            q.push( {curr->left, hdist - 1} );
        if(curr->right != NULL)
            q.push( {curr->right, hdist + 1} );
    }
    for(auto it : mp)
        cout << it.second << " ";
}


int main(){
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->right->left = new Node(5);
    root->right->right = new Node(6);
    root->right->left->left = new Node(7);
    root->right->left->right = new Node(8);


    TopView(root);

    // Implementing NodeKth - Kth smallest element in BST
    /*
    NodeKth *rootK = NULL;
    int keys[] = {1,2,3,4,5};
    for(int x : keys)
        rootK = insert(rootK, x);
    */
    return 0;
}