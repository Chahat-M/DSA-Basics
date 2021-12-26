#include <iostream>
#include <vector>
using namespace std;

// Creating a basic linked list
// 2 steps - create a struct Node, assign values to the node and link them to create the list
struct Node
{
    int data;   // to store the values
    Node *next; // stores the address of the next Node, data type of next node is Node itself
    // Creating a constructor to initialize the linked list
    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

// Traversing a singly linked list
// The function takes the head of the linked list as its parameter
void printList(Node *head)
{
    Node *curr = head; // Creating a node that initially starts as the head
    while (curr != NULL)
    {
        cout << curr->data << " ";  // To print the values of the list
        curr = curr->next;         // Moved to the next node
    }
}

// Recursive traversal of linked list
void printRec(Node *head)
{
    if (head == NULL)
        return;
    cout << head->data << " ";
    printRec(head->next);
}

// Inserting element at the beginning of the list and returning the head of the list
Node *insertBegin(Node *head, int x)
{
    Node *curr = new Node(x);
    curr->next = head;
    return curr;
}

// Inserting element at the end of the list and returning the head of the list
Node *insertEnd(Node *head, int x)
{
    Node *temp = new Node(x);
    if (head == NULL)
        return temp;
    Node *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    return head;
}

// Deleting first node of the linked list and returning the new head node
Node *delNode(Node *head){
    if(head == NULL)
        return NULL;
    else{
        Node *temp = head->next; //Storing the next element in a variable
        delete head; // Deleting the head element and deallocating the memory
        return temp; // Returning the new head
    }
}

// Deleting the last node of the linked list and returning head of the list
Node *delLast(Node *head){
    // When list is empty
    if(head == NULL)
        return NULL;
    
    // When list has only 1 element then also it deletes it
    // Here this case is separately required because for list of 1 element head->next->next doesn't exists
    if(head->next == NULL){
        delete head;
        return NULL;
    }

    Node *temp = head;
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    delete temp->next; // Removing the address of next element and make it NULL so the list ends there itslef
    temp->next = NULL;
    return head;
}

// Inserting at a specified position
Node *insertAt(Node *head, int pos, int data){
    Node *value = new Node(data);

    // If the element has to be inserted at position 1
    if(pos == 1){
        value->next = head;
        return head;
    }

    Node *temp = head;

    // To handle cases where pos > size of linked list + 1
    if(temp == NULL){
        return head;
    }
    
    for(int i = 1; i < pos - 1; i++){
        temp = temp->next;
    }
    value->next = temp->next;
    temp->next = value;
    return head;
}

// Searching the element in the linked list and returning its position - O(n)
// Iterative approach - auxiliary space - O(1)
// ---------------------------------------------
int search(Node *head, int x){
    int pos = 1;
    while(head != NULL){
        if(head->data == x)
            return pos;
        head = head->next;
        pos++;   
    } 
    
    return -1;
}
//---------------------------------------------

// Recursive approach - auxiliary space - O(n)
//----------------------------------------------
int searchRec(Node *head, int x){
    if(head == NULL)
        return -1;
    if(head->data == x){
        return 1;
    }
    else{
        int rem = searchRec(head->next, x);
        if(rem == -1)
            return -1;
        else
            return rem + 1;
    }
}
//----------------------------------------------

// Inserting a node in a sorted manner
Node *insertSort(Node *head, int x){
    Node *curr = new Node(x);
    Node *temp = head;
    Node *var;
    if(temp == NULL)
        return curr;
    while(temp->next != NULL){
        if(temp->next->data >= x){
            var = temp->next;
            temp->next = curr;
            curr->next = var;
            return head;
        }
        temp = temp->next;
    }
    // The case where node is inserted at the end 
    temp->next = curr;
    curr->next = NULL;
    
    return head;
}

// To print the middle of the linked list
void middle(Node *head){   
    Node *temp = head;
    int count = 0;
    if(temp == NULL || temp->next == NULL){
        cout << temp->data;
    }
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    temp = head;
    count = count / 2;
    for(int i = 0; i < count; i++){
        temp = temp->next;
    }
    cout << temp->data;   
}

//------------------------------------------
/*
// To return the middle of the linked list instead of directly printing
int *middle(Node *head){   
    Node *temp = head;
    int count = 0;
    if(temp == NULL || temp->next == NULL){
        return &(temp->data);
    }
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    temp = head;
    count = count / 2;
    for(int i = 0; i < count; i++){
        temp = temp->next;
    }
    return &(temp->data);   
}
*/
//--------------------------------------------

// Efficient solution of printing the middle of the linked list
// Maintain 2 pointers slow and fast, slow moves 1 step and at same time fast moves 2 step forward
// When fast is at last, slow is at middle
void midEff(Node *head){
    Node *slow = head;
    Node *fast = head;
    if(head == NULL)
        cout << head;
    while(fast != NULL && fast->next != NULL){ // Odd and even list condition
        slow = slow->next;
        fast = fast->next->next;
    }
    cout << slow->data;
}

// To find nth node from end of the linked list and return it
Node *findNth(Node *head, int n){
    Node *temp = head;
    if(head == NULL){
        return head;
    }
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    temp = head;
    if(n > count)
        return NULL;
    else{
        n = count - n + 1; // nth element from end = (length - n + 1) from start
        for(int i = 1; i < n; i++){
            temp = temp->next;
        }
        return temp;    // the nth element
    }
}

// Efficient solution to find nth node from end
// Using two pointer concept
// Maintain first pointer n positions ahead i.e at (n+1)th node
// And second pointer in the beginning
// When first reaches NULL second is the required
Node *findNthEff(Node*head, int n){
    Node *first = head;
    Node *second = head;
    for(int i = 0; i < n; i++){
        if(first == NULL) // n > length
            return NULL;
        first = first->next;
    }
    while(first != NULL){
        second = second->next;
        first = first->next;
    }
    return second;
}

// Reversing a linked list
//----------------------------------------------------------------------------------------------------
// Maintaining an auxiliary array and solving
Node *reverse(Node *head){
    vector<int> arr; // Creating an auxiliary array 
    // Storing all nodes of list as elements in the array
    for(Node *curr = head; curr != NULL; curr = curr->next){
        arr.push_back(curr->data);
    }
    // Retrieving all the elements from last and changing the list to reverse it
    for(Node *curr = head; curr != NULL; curr = curr->next){
        curr->data = arr.back(); // Makes the last element of the array as the node from beginning
        arr.pop_back(); // Deletes the last element of the array
    }
}
//------------------------------------------------------------------------------------------------------

// Effective solution to reverse a list - imp
Node *reverseEff(Node *head){
    Node *next, *prev = NULL;
    Node *curr = head;
    while(curr != NULL){
        next = curr->next; // storing the info of next node 
        curr->next = prev; 
        prev = curr;
        curr = next;    // Moving to next node 
    }
    return prev; // curr becomes NULL so prev is the original last element and new head
}

// Recursive solution to reverse a singly linked list - imp
// Method - 1
// Reversing the last n-1 nodes and then linking the first node and the rest of the reversed list
Node *reverseRec(Node *head){
    if(head == NULL || head->next == NULL)
        return head;
    Node *rest_head = reverseRec(head->next);
    Node *rest_tail = head->next;
    rest_tail->next = head;
    head->next = NULL;
    return rest_head; 
}

// Method - 2
// Reversing the first n-1 nodes and then linking the last nth node and the rest of the reversed list
Node *reverseRec2(Node *curr, Node *prev){
    if(curr == NULL)
        return prev;
    Node *next = curr->next;
    curr->next = prev;
    return reverseRec2(next, curr);
}

// Removing duplicates from a sorted linked list
Node *duplicate(Node *head){
    Node *curr = head;
    while(curr != NULL && curr->next != NULL){
        if(curr->data == curr->next->data){
            Node *temp = curr->next;
            curr->next = temp->next;
            delete temp; // Deallocating memory 
        }
        else{
            curr = curr->next;
        }
    }
    return head;
}

// Reverse a linked list in groups of k - imp

int main()
{
    // Assigning the values
    Node *head = new Node(10); // Creating the head of linked list which stores the value 10
    Node *tmp1 = new Node(15);
    Node *tmp2 = new Node(20);
    Node *tmp3 = new Node(30);
    // Adding addresses of next nodes
    head->next = tmp1; // head node stores address of tmp1 node
    tmp1->next = tmp2; // tmp1 node stores address of tmp2 node
    tmp2->next = tmp3;
    tmp3->next = tmp1;
    // Area for trying the last function
    //printList(temp);
    //+++++++++++++++++++++++++++++++++

    // Short implementation
    // ------------------------------------------------------------
    /*
    Node *head = new Node(10);
    head->next = new Node(20); //Directly storing the next value
    head->next->next = new Node(30);
    */
    // --------------------------------------------------------------

    return 0;
}