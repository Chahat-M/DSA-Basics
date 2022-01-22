// Advantage of BST - Reduces time complexity of basic operations
//                  - Like search, insert, delete, sorted traversal 

#include <iostream>
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



int main(){
    Node *root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    //root->left->left = new Node(20);
    //root->left->right = new Node(40);
    root->right->left = new Node(12);
    root->right->right = new Node(30);

    cout << ceilNode(root, 14)->data;
    return 0;
}