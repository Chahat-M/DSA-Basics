// Queue data structure
// First In First Out

#include <iostream>
#include <stack>
#include <queue>    // STL Library for queue
using namespace std;

// Creating queue structure using array
struct myQueue{
    int size, cap;
    int *arr;

    myQueue(int x){
        cap = x;
        size = 0;
        arr = new int[cap];
    }

    bool isFull(){
        return (size == cap);
    }

    bool isEmpty(){
        return (size == 0);
    }

    void enqueue(int x){
        if(isFull())
            return;
        arr[size] = x;
        size++;
    }

    void dequeue(){
        if(isEmpty())
            return;
        for(int i = 0; i < cap; i++)
            arr[i] = arr[i+1];
        size--;
    }

    int getFront(){
        if(isEmpty())
            return -1;
        else
            return arr[0];
    }

    int getRear(){
        if(isEmpty())
            return -1;
        else
            return arr[size-1];
    }
};

// Creating queue structure using circular array implementation - imp
// This will make dequeue O(1)
struct Queue{
    int cap, size, front;
    int *arr;

    Queue(int x){
        arr = new int(cap);
        cap = x;
        size = 0;
        front = 0;
    }

    bool isEmpty(){
        return (size == 0);
    }

    bool isFull(){
        return (size == cap);
    }

    int getRear(){
        if(isEmpty())
            return -1;
        else
            return (front + size - 1) % cap;
    }

    // Item added at the rear if the queue
    void enqueue(int x){
        if(isFull())
            return;
        int rear = getRear();
        rear = (rear+1) % cap;
        arr[rear] = x;
        size++;

    }

    // Item removed from the front
    void dequeue(){
        if(isEmpty())
            return;
        front = (front+1) % cap;
        size--;
    }

};

// Creating queue structure using linked list
struct Node{
    int data;
    Node *next;
    Node(int x){
        data = x;
        next = NULL;
    }
};

struct myQueue_LL{
    Node *front;
    Node *rear;
    int size;

    myQueue_LL(){
        front = NULL;
        rear = NULL;
        size = 0;
    }

    void enqueue(int x){
        Node *item = new Node(x);
        if(front == NULL){
            front = rear = NULL;
            return;
        }
        rear->next = item;
        rear = item;
        size++;
    }

    void dequeue(){
        Node *temp = front;
        if(front == NULL)
            return;
        front = front->next;
        if(front == NULL){  // Removed the last element
            rear = NULL;
        }
        delete(front);
        size--;
    }

    int getSize(){
        return size;
    }

    bool isEmpty(){
        return (front == NULL);
    }

    int getFront(){
        return front->data;
    }

    int getRear(){
        return rear->data;
    }
};

// Implementing stack using queue
struct myStack{
    queue<int> q1, q2;

    // In queue the item is added at the end of the queue
    // But for stack we want it to be added ay first so that can be easily popped out
    void push(int x){
        while(q1.empty() == false){
            q2.push(q1.front()); // Adds the first element of q1 to q2
            q1.pop(); // Removes the first element of q1
        }
        q1.push(x);
        while(q2.empty() == false){
            q1.push(q2.front()); // Adds the first element of q2 after the newly added element in q1
            q2.pop(); // Clearing q2 for reuse
        }
    }

    // Removing the top most element of the stack
    // Ot removing the first element of the queue
    void pop(){ 
        q1.pop();
    }

    int size(){
        return q1.size();
    }

    int top(){
        q1.front(); 
    }
};

// Reversing a queue
//------------------------------------------------------------------------------------
// Iterative method:
// Create a stack and push every item to it, so when they will be popped it's order is reversed
void reverseIt(queue<int> q1){
    stack<int> st;
    // Adding elements to the stack
    while(q1.empty() == false){
        st.push(q1.front());
        q1.pop();
    }

    // Removing elements from the stack and pushing back to the queue
    while(st.empty() == false){
        q1.push(st.top());
        st.pop();
    }
}

// Pop the top element, reverse the rest of the queue, add the element ti the end
void reverseRec(queue<int> q1){
    if(q1.empty())
        return;
    int c = q1.front();
    q1.pop();
    reverseRec(q1); 
    q1.push(c);
}

// Generate a number from given set of digits
void printNum(int num){
    queue<string> q1;
    q1.push("5");
    q1.push("6");
    for(int i = 0; i < num; i++){
        string curr = q1.front();
        cout << curr << " ";
        q1.pop();
        q1.push(curr + "5");
        q1.push(curr + "6");
    }
}



int main(){
    printNum(10);
    return 0;
}