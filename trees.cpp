// Trees data structure

#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

// Binary tree data structure
struct Node{
    int data;
    Node *left; // Left child of the node
    Node *right; // Right child of the node

    Node(int x){
        data = x;
        left = NULL; // In Java initializing this isn't required, self-initialized as null
        right = NULL;
    }
};

// Tree traversal
// Total depth traversal possible ways - 3! = 6
// 3 are the most popular 

/* Depth traversal - 1. Inorder
                     2. Preorder
                     3. Postorder
*/

// Inorder traversal implementation
// Inorder - left_subtree root right_subtree
// Time complexity - constant time for each node => O(n)
// Auxiliary space - no. of function calls = no. of nodes from root to leaf = height of binary tree
//                 - O(h+1) ~ O(h) , h = height of binary tree
// Output - leaf to root
void inTraversal(Node *root){
    if(root == NULL)
        return;
    inTraversal(root->left);
    cout << root->data << " ";
    inTraversal(root->right);
}

// Preorder traversal implementation
// Preorder - root left_subtree right_subtree
// Time complexity and auxiliary space - same as inorder
void preTraversal(Node *root){
    if(root == NULL)
        return;
    cout << root->data << " ";
    preTraversal(root->left);
    preTraversal(root->right);
}

// Postorder Traversal implementation
// Postorder - left_subtree right_subtree root
// Time complexity and auxiliary space - same as inorder
void postTraversal(Node *root){
    if(root == NULL)
        return;
    postTraversal(root->left);
    postTraversal(root->right);
    cout << root->data << " ";
}

// Height of binary tree
// No. of nodes from root to leaf (including both) in the longest path
// = No. of levels in the tree
// Time complexity - O(n), constant work for every node
// Auxiliary space - O(h)
int treeHeight(Node *root){
    if(root == NULL)
        return 0;
    return max(treeHeight(root->left), treeHeight(root->right)) + 1; // +1 for root node
}

// Print nodes at a distance of K - imp
// Time complexity - O(n)
// AUxiliary space - O(h) 
void distNodes(Node *root, int k){
    if(root == NULL)
        return;
    if(k == 0){
        cout << root->data << " ";
    }
    else{
        distNodes(root->left, k-1);
        distNodes(root->right, k-1);
    }
}

// Level Order Traversal or Breadth Order Traversal
//----------------------------------------------------------------------------------------
/* Method 1
    Find height of the tree = no. of levels
    Print all nodes at distances 0, 1, 2 ... (height-1)
    Time complexity - O(h*n)
*/
void levelTraversal(Node *root){
    int level_num = treeHeight(root); // O(n)
    for(int i = 0; i < level_num; i++){  // runs for height h times
        distNodes(root, i);             // O(n)
    }
    return;
}

/* Method 2
    Using queue data structure
    First enqueue the root, then dequeue and print it
    While dequeue add it's children to the queue
    Time complexity - O(n)
    Auxiliary space - Theta(W), W = width of tree = nodes in last level 
*/
void levelTraversalEff(Node *root){
    if(root == NULL)
        return;
    queue<Node*> q1;
    q1.push(root);
    while(q1.empty() == false){
        Node *curr = q1.front();
        q1.pop();
        cout << curr->data << " ";
        if(curr->left != NULL)
            q1.push(curr->left);
        if(curr->right != NULL)
            q1.push(curr->right);
    }
}
//--------------------------------------------------------------------------------------------------

// Level order traversal line by line - printing one level in a line
//-----------------------------------------------------------------------------------------
/* Method 1
    -When you travel through last node of the level, the next level is in the queue already
    -Time complexity - O(n)
    -Auxiliary space - theta(width) = O(n)
*/
void lineTraversal1(Node *root){
    if(root == NULL)
        return;
    queue<Node*> q1;
    q1.push(root);
    q1.push(NULL);
    while(q1.size() > 1){
        Node *curr = q1.front();
        q1.pop();
        if(curr == NULL){
            cout << endl;
            q1.push(NULL);
            continue;
        }
        else
            cout << curr->data << " ";
        if(curr->left != NULL)
            q1.push(curr->left);
        if(curr->right != NULL)
            q1.push(curr->right);
    }
}

/* Method 2
    Using two loops, printing nodes of a level and printing next line
    Time complexity - O(n)
    Auxiliary space - theta(width) = O(n)
*/
void lineTraversal2(Node *root){
    if(root == NULL)
        return;
    queue<Node*> q1;
    q1.push(root);
    while(q1.empty() == false){
        int count = q1.size();
        for(int i = 0; i < count; i++){
            Node *curr = q1.front();
            q1.pop();
            cout << curr->data << " ";
            if(curr->left != NULL)
                q1.push(curr->left);
            if(curr->right != NULL)
                q1.push(curr->right);
        }
        cout << endl;
    }
}
//---------------------------------------------------------------------------------------------------

// Size of binary tree 
// = No. of nodes in the binary tree
// Time complexity - O(n)
// Auxiliary space - O(h)
int treeSize(Node *root){
    if(root == NULL)
        return 0;
    return treeSize(root->left) + treeSize(root->right) + 1;
}

// Maximum in binary tree
// Time complexity - O(n)
// Auxiliary space - O(h)
// For skewed tree - iterative solution is better, for perfect tree - recursive solution is better
int treeMax(Node *root){
    if(root == NULL)
        return INT16_MIN;
    return max(root->data, max(treeMax(root->left), treeMax(root->right)));
}

// Printing left view of Binary tree
//----------------------------------------------------------------------------------------------------------------------------
/* Method 1 - Iterative method
    Using level order traversal line by line concept
    Time complexity - O(n)
    Auxiliary space - theta(width) ~ O(n)
*/
void leftView1(Node *root){
    queue<Node*> q1;
    q1.push(root);
    while(q1.empty() == false){
        int count = q1.size();
        cout << q1.front()->data << " "; // Prints the left most which is the first element of the queue
        for(int i = 0; i < count; i++){
            Node *curr = q1.front();
            q1.pop();
            if(curr->left != NULL)
                q1.push(curr->left);
            if(curr->right != NULL)
                q1.push(curr->right);
        }
    }
}

/* Method 2 - Recursive method
    Using preorder traversal concept
    Time complexity - O(n)
    Auxiliary space - O(h)
*/
int maxlevel = 0;
void leftView2(Node *root, int level){ // Call as leftView(root, 1)
    if(root == NULL)
        return;
    if(maxlevel < level){
        cout << root->data << " ";
        maxlevel = level;
    }
    leftView2(root->left, level+1);
    leftView2(root->right, level+1);
}
//-------------------------------------------------------------------------------------------------------------------

// Children Sum Property
// Sum of values of left and right child = value of parent
// Time complexity - O(n)
// AUxiliary space - O(h)
bool childrenSum(Node *root){
    int val = 0;
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return 1;
    if(childrenSum(root->left) && childrenSum(root->right)){
        if(root->left != NULL)
            val += root->left->data;
        if(root->right != NULL)
            val += root->right->data;
        if(val == root->data)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

// Check for balanced Binary Tree
// Difference between left subtree and right subtree <= 1 at every node
//---------------------------------------------------------------------------------------------------------------
/* Method 1
    Time complexity - O(n^2)
    Auxiliary space - O(h)
*/
bool isBalanced1(Node *root){
    int left_height = treeHeight(root->left);
    int right_height = treeHeight(root->right);
    return (abs(left_height - right_height) <= 1 && isBalanced1(root->left) && isBalanced1(root->right));
}

/* Method 2 - imp
    Returns -1 if unBalanced else returns height
    Time complexity - O(n)
*/
int isBalanced2(Node *root){
    if(root == NULL)
        return 0;
    int left_height = isBalanced2(root->left);
    if(left_height == -1)
        return -1;
    int right_height = isBalanced2(root->right);
    if(right_height == -1)
        return -1;
    if(abs(left_height - right_height) > 1) // Unbalanced condition
        return -1;
    else 
        return max(left_height, right_height) + 1; 
}
//----------------------------------------------------------------------------------------------------------------

// Maximum width of binary tree
// Using level order Traversal line by line concept
// Time complexity - O(n)
// Auxiliary space - theta(width) ~ O(n)
int maxWidth(Node *root){
    if(root == NULL)
        return 0;
    queue<Node*> q1;
    q1.push(root);
    int count = 0;
    while(q1.empty() == false){
        int length = q1.size();
        count = max(count, length); // count = max(count, q1.size()) shows error ?
        for(int i = 0; i < length; i++){
            Node *curr = q1.front();
            q1.pop();
            if(curr->left != NULL)
                q1.push(curr->left);
            if(curr->right != NULL)
                q1.push(curr->right);
        }
    }
    return count;
}

// Convert a binary tree to Doubly Linked List in place - imp
// "in place" means using the same memory that is assigned to the tree nodes instead of creating new memory for list nodes
// Using Inorder Traversal (left, root, right)
// Returns Node head
// Time complexity - O(n)
// Auxiliary space - O(h)
Node *treeTodll(Node *root){
    if(root == NULL)
        return NULL;
    static Node *prev = NULL; // Because of static keyword value of prev will be carried in function calls
    Node *head = treeTodll(root->left); // Left subtree traversal
    if(prev == NULL)
        head = root;
    else{
        root->left = prev;   // Node 1 <- Node 2
        prev->right = root; // Node 1 -> Node 2
        // Node 1 <-> Node 2
    }
    prev = root;
    treeTodll(root->right); // Right subtree traversal
    return head;
}

// Construct Binary Tree from Inorder and Preorder
/* NOTE : 1. Can construct when two traversals are given 
          2. Can't construct a binary tree if Inorder traversal is not given
*/
// Time complexity - O(n^2), (O(n) for every node)
// But with hashing - O(n)
int preIndex = 0;
Node *conTree(int inorder[], int preorder[], int start, int end){
    if(start > end)
        return NULL;
    // Finding root
    Node *root = new Node(preorder[preIndex++]); // Preorder - (root, left, right)
    // Finding index of root
    int index;
    for(int i = start; i <= end; i++){
        if(inorder[i] == root->data){
            index = i;
            break;
        }
    }
    root->left = conTree(inorder, preorder, start, index-1); // Left Subtree
    root->right = conTree(inorder, preorder, index+1, end); // Right Subtree
    return root;
}

// Tree traversal in spiral form
//------------------------------------------------------------------------------------------------------------
/* Method 1
    The level which has to be printed from right to left is pushed to stack
    As the stack reverses the usual order (left to right) 
    Time complexity - O(n) , items that are printed reverse are addressed 4 times and others are addressed twice
*/
void spTraversal1(Node *root){
    queue<Node*> q1;
    stack<int> st;
    q1.push(root);
    int level = 0;
    while(q1.empty() == false || st.empty() == false){
        int count = q1.size();
        for(int i = 0; i < count; i++){
            Node *curr = q1.front();
            q1.pop();
            // For odd levels we need to traverse from right to left
            // So that data should be pushed to stack so that can be printed in a reverse way
            if(level % 2 != 0)
                st.push(curr->data);
            else
                cout << curr->data << " ";
            if(curr->left != NULL) q1.push(curr->left);
            if(curr->right != NULL) q1.push(curr->right);
        }
        if(level % 2 != 0){
            while(st.empty() == false){
                cout << st.top() << " ";
                st.pop();
            }
        }
        level++;
    }
}

/* Method 2
    Use two stacks - one for levels that are travelled from left to right
    Another for levels travelled from right to left 
    Time complexity - O(n) , every item is addressed twice
*/
void spTraversal2(Node *root){
    stack<Node*> st1;
    stack<Node*> st2;
    st1.push(root);
    while(st1.empty() == false || st2.empty() == false){
        while(st1.empty() == false){
            Node *curr1 = st1.top();
            st1.pop();
            cout << curr1->data << " ";
            if(curr1->left != NULL) st2.push(curr1->left);
            if(curr1->right != NULL) st2.push(curr1->right);
        }
        while(st2.empty() == false){
            Node *curr2 = st2.top();
            st2.pop();
            cout << curr2->data << " ";
            // This stack has Node right most node at top
            // So in the other stack, to print it from left to right
            // We need to push the right child node before the left node
            if(curr2->right != NULL) st1.push(curr2->right);
            if(curr2->left != NULL) st1.push(curr2->left);
        }
    }   
}
//------------------------------------------------------------------------------------------------------

// Diameter of Binary Tree - imp
// Longest path from one leaf node to the other leaf node
//-------------------------------------------------------------------------------------------------------
/* Method 1
    Using height of tree
    Time complexity - O(n^2)
*/
int treeDia(Node *root){
    if(root == NULL)
        return 0;
    int left_height = treeHeight(root->left);
    int right_height = treeHeight(root->right);
    int diameter = 1 + left_height + right_height;
    return max(max(diameter, treeDia(root->left)), treeDia(root->right));
}

/* Method 2
    Using hashing - Store the height of every node in a hash table
    Pass the hash table as an argument, and use it to know the height in O(1)
    Time complexity - O(n)
    Auxiliary space - O(n), because of hash table
*/

/* Method 3
    Modify height function
    While calculating the height, calculate diameter itself
    Time complexity - O(n)
    No overhead, Auxiliary space - O(h)
*/
int diameter = 0;
int heightNdia(Node *root){
    if(root == NULL)
        return 0;
    int left_height = heightNdia(root->left);
    int right_height = heightNdia(root->right);
    // The 1 line modification - 
    diameter = max(diameter, 1 + left_height + right_height);   // Sets the diameter
    return max(left_height,right_height) + 1;   // Returns height
}
//-------------------------------------------------------------------------------------------------------

// Lowest Common Ancestor of two nodes - imp
// Lowest in terms of the level not it's value
// Can be used to find distance between two nodes as well
//-------------------------------------------------------------------------------------------------------
/* Method 1
    Use two arrays to store the path nodes from root to the given node
    Then traverse the array, the last matching value is the lowest common ancestor LCA
    Time complexity - O(n)
*/

// To find the path from root to the given node
// Returns true and fills the path vector, else returns false if node is not present in the tree
// Time complexity - O(n)
bool findPath(Node *root, vector<Node*> path, int val){
    if(root == NULL)
        return false;
    path.push_back(root); // Pushing root to the vector
    if(root->data == val)
        return true;
    // If present in left or right subtree
    if(findPath(root->left, path, val) || findPath(root->right, path, val))
        return true;
    path.pop_back(); // If not present in left or right subtree so, that node is not an ancestor, thus removed
    return false;   
}

// Time complexity - O(n)
// Auxiliary space - O(n)
Node *nodesLCA(Node *root, int val1, int val2){
    vector<Node *> path1, path2;
    // Both nodes should be unique
    if(val1 == val2)
        return NULL;
    // If both the nodes exist, then only LCA can be found
    if(findPath(root, path1, val1) && findPath(root, path2, val2)){
        for(int i = 0; i < path1.size() - 1 && i < path2.size() - 1; i++){
            cout << path1[i]->data << " " << path2[i]->data << endl;
            if(path1[i+1] != path2[i+1])
                return path1[i];
        }
    }
    for(int i = 0; i < path1.size() - 1 && i < path2.size() - 1; i++){
        cout << path1[i]->data << " " << path2[i]->data << endl;
    }
    return NULL;
}

/* Method 2 - Efficient Solution
    Assumption that both node exist, if one node exists but other doesn't, returns pointer to the node present
    Time complexity - O(n)
    Auxiliary space - O(h)
    Why efficient - requires 1 traversal instead of 2
                    less space in worst case
*/
Node *nodesLCAeff(Node *root, int val1, int val2){
    if(root == NULL)
        return NULL;
    if(root->data == val1 || root->data == val2)
        return root;
    Node *lca1 = nodesLCAeff(root->left, val1, val2);
    Node *lca2 = nodesLCAeff(root->right, val1, val2);
    // When one node is in left subtree and the other in right subtree - the root is the lca
    if(lca1 != NULL && lca2 != NULL) // Here lca1 = any one given node and lca2 = other given node 
        return root;
    // When both nodes are present in left subtree
    if(lca1 != NULL)
        return lca1;
    // When either both are present in right subtree(lac2 != NULL) 
    // Or both aren't present, lca1 = lca2 = NULL
    else    
        return lca2;
    
}
//---------------------------------------------------------------------------------------------------------------------

// Burn a binary tree from a leaf - very imp
// Takes 0sec to burn the leaf, +1sec to burn all adjacent at same time, then +1sec to burn their adjacent and so on
/* Approach - 
    Farthest distance of the nodes from the leaf via its ancestors
    Find the distance of the leaf node from its ancestors 
    See if it is in left of ancestor or right
    Add the distance to the opposite height of the ancestor node
    To return the height of the tree and update the time in a variable simultaneously
*/
// Refer Diameter of Binary Tree 
// Time complexity - O(n)
// Auxiliary space -  
int burnTime(Node *root, int leaf, int &dist, int &result){
    if(root == NULL)
        return 0;
    if(root->data == leaf){
        dist = 0;
        return 1;
    }
    // ldist = distance of left child from given leaf node, similarly rdist
    int ldist = -1, rdist = -1;
    int left_height = burnTime(root->left, leaf, ldist, result);    // sets left height of the node and also values of ldist and result
    int right_height = burnTime(root->right, leaf, rdist, result);

    // The further if else if condition will hold only for ancestors of leaf node

    // The leaf is in the left of the current node (present root)
    // So the longest path - dist of leaf till root + right height of root
    if(ldist != -1){
        dist = ldist + 1;   // Distance of leaf from current node
        result = max(result, right_height + dist);
    }
    // The leaf is in the right of the current node/root
    // So longest path - dist of leaf till root + left height
    else if(rdist != -1){
        dist = rdist + 1;
        result = max(result, left_height + dist);
    }
    return max(left_height, right_height) + 1;    // Returns height of the current node
}

// Count nodes in a complete binary tree
/* Complete binary tree - All levels should be completely filled except the last
                        - Last level should be filled from left to right
*/
//------------------------------------------------------------------------------------------------------

/* Method 1
    Works for every binary tree
    Time complexity - O(n)
*/
int nodeCount(Node *root){
    if(root == NULL)
        return 0;
    return nodeCount(root->left) + nodeCount(root->right) + 1; // +1 for root of the tree
}

/* Method 2 - Efficient solution
    Breaking the binary tree into perfect binary tree 
    Time complexity - O(logn * logn) - refer video
*/
int nodeCountEff(Node *root){
    int left = 0, right = 0;
    Node *curr = root;
    // Finding the level with leftmost node - O(h)
    while(curr != NULL){
        left++;
        curr = curr->left;
    }
    curr = root;
    // Finding the level with the rightmost node - O(h)
    while(curr != NULL){
        right++;
        curr = curr->right;
    }
    // If leftmost and rightmost node are in same level - perfect binary tree
    if(left == right)
        return pow(2, left) - 1;
    // Otherwise repeat to find perfect binary subtree
    return 1 + nodeCountEff(root->left) + nodeCountEff(root->right);
}
//------------------------------------------------------------------------------------------------------------

// Serialization of a binary tree - imp
// Converting a binary tree to array/string such that it can be regenerated
// Store null values as -1, assuming -1 is not in the tree
// Traverse in any order of your choice - (inorder, preorder, postorder)
// Here - Preorder (root left right)
// Time complexity - O(n), Auxiliary space - O(n)
void serialize(Node *root, vector<int> &arr){
    if(root == NULL){
        arr.push_back(-1);
        return;
    }
    arr.push_back(root->data);
    serialize(root->left, arr);
    serialize(root->right, arr);
}

// Deserialization of a binary tree
// Regenerating the tree from the given array/string
// Preorder traversal (root left right)
// Time complexity - O(n)
Node *deserialize(vector<int> arr){
    static int index = 0;
    if(index == arr.size())
        return NULL;
    int val = arr[index];
    index++;
    if(val == -1)
        return NULL;
    Node *root = new Node(val);
    root->left = deserialize(arr);
    root->right = deserialize(arr);
    return root;
}

// Iterative Inorder Traversal (left root right)
// Time complexity - O(n)
// Auxiliary space - O(h)
void inTraversal_it(Node *root){
    if(root == NULL)
        return;
    stack<Node*> st;
    Node *curr = root;
    while(curr != NULL || st.empty() == false){
        while(curr != NULL){
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

// Iterative Preorder Traversal (root left right)
// Time complexity - O(n)
// Auxiliary space - O(n)
void preTraversal_it(Node *root){
    if(root == NULL)
        return;
    stack<Node*> st;
    st.push(root);
    while(st.empty() == false){
        Node *curr = st.top();
        st.pop();
        cout << curr->data << " ";
        if(curr->right != NULL)
            st.push(curr->right);
        if(curr->left != NULL) // So that left is at top
            st.push(curr->left); 
    }
}

// Space Optimized solution
// Print root and all left nodes and add right nodes to the stack 
// Time Complexity - O(n)
// Auxiliary Space - O(h)
void preTraversal_itEff(Node *root){
    if(root == NULL)
        return;
    stack<Node*> st;
    st.push(root);
    Node *curr = root;
    while(curr != NULL || st.empty() == false){
        while(curr != NULL){
            cout << curr->data << " ";
            if(curr->right != NULL)
                st.push(curr->right);
            curr = curr->left;
        }
        if(st.empty() == false){
            curr = st.top(); // When left nodes are over and right has to be accessed
            st.pop();
        } 
    }
}


int main(){
    Node *root = new Node(1);  //          10
    root->left = new Node(2); //        /     '\' 
    root->right = new Node(3); //     20      30
    // Fun fact - Why we can't use '\' without quotes ?
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    preTraversal(root);
    return 0;
}