#include <iostream>
using namespace std;

// Creating the basic node structure for doubly linked list
struct Node{
    int data;
    Node *prev;
    Node *next;
    
    //Creating constructor to initialize
    Node(int x){
        data = x;
        prev = NULL;
        next = NULL;
    }
};

// To print the doubly linked list
void printList(Node *head){
    while(head != NULL){
        cout << head->data << " ";
        head = head->next;
    }
}

// Insert a node at the beginning of the list and return the modified node
Node *insert(Node *head, int data){
    Node *tmp1 = new Node(data);
    tmp1->next = head;
    if(head != NULL)
        head->prev = tmp1;
    return tmp1; 
}

// Insert a node at the end of the doubly linked list
Node *insertEnd(Node *head, int data){
    Node *tmp = new Node(data);
    Node *curr = head;
    if(head == NULL)
        return tmp;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = tmp;
    tmp->prev = curr;
    return head;
}

// Reverse a doubly linked list
Node *reverse(Node *head){
    Node *curr = head;
    Node *temp = NULL;
    if(head == NULL || head->next == NULL)
        return head;
    while(curr != NULL){     // head != NULL ?
        temp = curr->next;
        curr->next = curr->prev;
        curr->prev = temp;
        curr = curr->prev; // head = head->next ?
    }
    return temp->next;    // return head or head->prev ?
}

// Delete head node of doubly linked List
Node *delHead(Node *head){
    if(head == NULL || head->next == NULL){
        delete head; 
        return NULL;
    }
    Node *temp = head;
    head = head->next;
    head->prev = NULL;
// In C++ deallocating memory is necessary so delete the previous head separately
// In Java memory is deallocated automatically, so not required
    delete temp;
    return head;
}

Node *delLast(Node *head){
    if(head == NULL || head->next == NULL){
        delete head;
        return NULL;
    }
    Node *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    // the pointer is at last element, so to have 2nd last element
    temp = temp->prev;
    temp->next = NULL; // setting the 2nd last element's next pointer to NULL
    delete temp->next; // deleting the last node, deallocating memory
    return head;
}

int main(){
    // Assigning the values to a doubly linked list
    Node *head = new Node(10);
    Node *temp1 = new Node(20);
    Node *temp2 = new Node(30);
    head->next = temp1;         // For 1st node
    temp1->next = temp2;       // For 2nd node
    temp1->prev = head;
    temp2->prev = temp1;        // For 3rd node 
    Node *tmp = delLast(head);
    printList(tmp); 

    return 0;
}