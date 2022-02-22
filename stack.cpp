#include <iostream>
#include <vector>
#include <string>
#include <ctype.h>
#include <math.h>
#include <stack> // STL library
using namespace std;

// Stack - Last In First Out Data Structure

// Creating a stack structure on own
// Array implementation
// Fixed capacity, O(1) for all operations
struct myStackArr{
    int *arr;
    int cap; // Size of the stack/array
    int top; // The point till which stack is filled

    // Creating the constructor
    myStackArr(int c){
        cap = c;
        arr = new int[cap]; // Initializing the array
        top = -1;
    }

    // Defining push operation to add the element to the stack
    void push(int x){
        if(top == cap - 1){
            cout << "Overflow Condition" << endl;
            return;
        }
        top++; // Bcoz initially top = -1
        arr[top] = x;
    }

    // Defining pop operation to remove the last/topmost element of stack and return it
    int pop(){
        if (top == -1){
            cout << "Underflow condition" << endl;
            return -1;
        }
        int res = arr[top]; // Storing the topmost element so that we can return it
        top--;
        return res;
    } 

    // Defining peek operation to return the topmost element of the stack
    int peek(){
        if (top == -1){
            cout << "Underflow condition" << endl;
            return -1;
        }
        return arr[top];
    }

    // Defining size operation to return the size of the stack
    int size(){
        return top + 1; // top indexing starts with 0 
    }

    // Defining isEmpty function to test if the stack is empty or not
    // Returns 1 if stack is empty
    bool isEmpty(){
        return (top == -1);  // Default value of top is -1 i.e no new element added
    }
};

// Vector implementation
// Dynamic size, Avg time complexity = O(1)
// Worst case for push and pop = linear O(n)
struct myStackVect{
    vector<int> vect;

    void push(int x){
        vect.push_back(x);
    }

    int pop(){
        int res = vect.back(); // back() returns the last element of the vector
        vect.pop_back(); // Removes the last element
        return res;
    }

    int peek(){
        return vect.back();
    }

    int size(){
        return vect.size(); // size() function of vector returns its length
    }

    bool isEmpty(){
        return vect.empty();
    }

};

// Linked List implementation
struct Node{
    int data;
    Node *next;
    Node(int x){
        data = x;
        next = NULL;
    }
};

struct myStackList{
    Node *head;
    int len;

    myStackList(){
        head = NULL;
        len = 0;
    }

    void push(int x){
        Node *temp = new Node(x);
        temp->next = head;
        head = temp;
        len++;
    }

    int pop(){
        if(head == NULL){  // Underflow condition
            return INT16_MAX;
        }
        int res = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        len--;
        return res;
    }

    int peek(){
        if(head == NULL){
            return INT16_MIN;
        }
        return head->data;
    }

    int size(){
        return len;
    }

    bool isEmpty(){
        return (len == 0);
    }
};

// Balanced parenthesis problem 
// The brackets that opens latest have to be closed first
// The allowed inputs are - (,),{,},[,]
// Used stack library
//----------------------------------------------------------------------------------------
bool matching(char a, char b){
    return ((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']'));
}

bool isBalanced(string str){
    stack<char> st; // Creating a stack object
    for(char x : str){
        // Adding only opening brackets to the stack
        if(x == '(' || x == '{' || x == '[')
            st.push(x);
        else{
            if(st.empty()){ //closing brackets are more
                return false;
            }
            if(matching(st.top(), x) == false){
                return false;
            }
            else{
                st.pop();
            }
        }
    }
    return (st.empty() == true);
}
//-------------------------------------------------------------------------------------

// Two stacks in an array
/* Method 1 - Divide the array into two halves and each half is one stack
            - But this wastes space as stack 1 can have more elements than stack 2
            - So it will not let stack 1 fill if half of the array is filled
*/
/* Method 2 - Fill first stack from front of array and second stack from behind
            - Space efficient method
*/
// Method 2 implementation 

struct twoStacks{
    int *arr;
    int cap;
    int top1, top2;

    twoStacks(int n){
        cap = n;
        top1 = -1; // Initially keeping them outside the array
        top2 = n;
        arr = new int(n); // creating the array of n size
    }

    void push1(int x){ // Filling first stack
        if(top1 < top2 - 1){ // if top1 == top2 - 1 , overflow condition
            top1++;
            arr[top1] = x; 
        }
    }

    void push2(int x){
        if(top1 < top2 - 1){ // if top1 == top2 - 1 , overflow condition
            top2--;
            arr[top2] = x; 
        }
    }

    int pop1(){
        if(top1 >= 0){
            int x = arr[top1];
            top1--;
            return x;
        }
        else{
            exit(1);
        }
    }

    int pop2(){
        if(top2 < cap){
            int x = arr[top2];
            top2++;
            return x;
        }
        else{
            exit(1);
        }
    }
};

// K stacks in an array


// Stock span Problem
//-------------------------------------------------------------------------------------------------------------------
// Span of a day = consecutive days on left including the day itself where stock price is less than or equal to the stock price of the day
// Naive solution
void printSpan(int arr[], int n){
    for(int i = 0; i < n; i++){
        int span = 1;
        for(int j = i - 1; j >= 0; j--){
            if(arr[j] <= arr[i]){
               span++; 
            }
            else break;
        }
        cout << "Span of " << i << "is - " << span <<endl;
    }
}

// Efficient solution - O(n)
// Span = Index of the element - Index of the previous greater element 
// If no previous greater element then span = index + 1;
void printSpanEff(int arr[], int n){
    stack<int> st;
    st.push(0); // Pushing index 0 to the stack 
    int span = 1;
    cout << "span of " << arr[0] << " is - " << span; // Span of first element is always 1
    
    for(int i = 1; i < n; i++){
        while(st.empty() == false && arr[st.top()] <= arr[i]){
            st.pop();
        }
        span = (st.empty()) ? i + 1 : i - st.top();
        cout << "span of " << arr[i] << " is - " << span; 
        st.push(i);
    }
}
//-------------------------------------------------------------------------------------------------------------------

// Previous greater element
void prevGreater(int arr[], int n){
    for(int i = 0; i < n; i++){
        int j;
        for(j = i - 1; j >= 0 ; j--){
            if(arr[j] > arr[i]){
                cout << arr[j] << " ";
                break;
            }
        }
        if(j == -1)
            cout << "-1" << " ";
    }
}

// Efficient solution - O(n)
void prevGreaterEff(int arr[], int n){
    stack<int> st;
    st.push(arr[0]);
    for(int i = 0; i < n; i++){
        while(st.empty() == false){
            if(st.top() > arr[i]){
                cout << st.top() << " ";
                st.push(arr[i]);
                break;
            }
            else{
                st.pop();
            }
        }
        if(st.empty()){
            cout << "-1" << " ";
            st.push(arr[i]);
        }
    }
}

// Next Greater Element
void nextGreater(int arr[], int n){
    stack<int> st;
    st.push(arr[n-1]);
    int rev[n];
    for(int i = n-1; i >= 0; i--){
        while(st.empty() == false){
            if(st.top() > arr[i]){
                rev[i] = st.top();
                st.push(arr[i]);
                break;
            }
            else{
                st.pop();
            }
        }
        if(st.empty()){
            rev[i] = -1;
            st.push(arr[i]);
        }
        
    }

    // Otherwise prints output in reverse order 
    for(int i = 0; i < n; i++)
        cout << rev[i] << " ";
}

// Largest rectangular area in a histogram - imp
//-------------------------------------------------------------------------------------------------------------------------------------
// Naive solution - O(n^2)
int histoArea1(int arr[], int n){
    int area = 0;
    for(int i = 0; i < n; i++){
        int curr_area = arr[i];
        // Checking right bars
        for(int j = i+1; j < n; j++){
            if(arr[j] < arr[i])
                break;
            curr_area += arr[i]; 
        }

        // Checking left bars
        for(int j = i-1; j >= 0; j--){
            if(arr[j] < arr[i])
                break;
            curr_area += arr[i];
        }
        area = max(area, curr_area);
    }
    return area;
}

// Better solution - O(n)
// Use previous smaller and next smaller element
// The next two functions are defined just below the histoArea2()
vector<int> prevSmallerIn(int arr[], int n);
vector<int> nextSmallerIn(int arr[], int n);

int histoArea2(int arr[], int n){
    vector<int> prev = prevSmallerIn(arr,n);
    vector<int> next = nextSmallerIn(arr,n);
    int area = 0,curr_area;
    for(int i = 0; i < n; i++){
        curr_area = arr[i]; // area of the particular bar
        curr_area += arr[i] * (i - prev[i] - 1); // area of the previous continuous smaller bars
        curr_area += arr[i] * (next[i] - i - 1);
        area = max(area, curr_area);
    }
    return area;
}

// For previous smaller element, returns vector of indices
vector<int> prevSmallerIn(int arr[], int n){
    stack<int> st;
    vector<int> prev;
    st.push(0);
    prev.push_back(-1); // No previous smaller element for the first element
    for(int i = 1; i < n; i++){
        while(st.empty() == false){
            if(arr[st.top()] > arr[i]){
                st.pop();
            }
            else{
                prev.push_back(st.top());
                st.push(i);
                break;
            }
        }
        if(st.empty() == true){
            prev.push_back(-1);
            st.push(i);
        }
            
    }
    return prev;
}

// For next smaller element, returns vector of indices
vector<int> nextSmallerIn(int arr[], int n){
    stack<int> st;
    vector<int> prev; // Stores the previous smaller element of the reversed array
    vector<int> next; // Stores the next smaller element in sequence
    st.push(n-1);
    prev.push_back(n); // No next smaller element for the last element
    for(int i = n-2; i >= 0; i--){
        while(st.empty() == false){
            if(arr[st.top()] > arr[i]){
                st.pop();
            }
            else{
                prev.push_back(st.top());
                st.push(i);
                break;
            }
        }
        if(st.empty() == true){
            prev.push_back(n);
            st.push(i);
        }  
    }
    for(int i = 0; i < n; i++){
        next.push_back(prev[n-1-i]);
    }
    return next;
}

// Best solution - Method 3
// Use previous smaller and next smaller element
int histoArea3(int arr[], int n){
    stack<int> st;
    int area = 0, curr_area, top;
    st.push(0);
    for(int i = 0; i < n; i++){
        while(st.empty() == false){
            if(arr[st.top()] >= arr[i]){
                top = st.top();
                st.pop();
                curr_area = arr[i] * (st.empty() ? i+1 : (i - top));
                st.push(i);
            }
            else{

                curr_area = arr[i];
            }
            area = max(area, curr_area);
            
        }
    }
}



//------------------------------------------------------------------------------------------------------------------------------------------------

// Finding largest rectangle (submatrix) with all 1s in a binary matrix - imp

// Designing a stack that supports getMin()
// Time complexity - O(1), Space complexity - O(n)
struct minStack{
    vector<int> vect;
    vector<int> min_vect;
    int minimum = INT16_MAX;

    void push(int x){
        vect.push_back(x);
        if(x < minimum){
            minimum = x;
            min_vect.push_back(minimum);
        }
    }

    int pop(){
        int res = vect.back();
        if(res == minimum){
            min_vect.pop_back();
        }
        minimum = min_vect.back();
        vect.pop_back();
        return res;
    }

    int getMin(){
        return minimum;
    }

    int peek(){
        return vect.back();
    }

    int size(){
        return vect.capacity();
    }
};

// Efficient way - imp
// Time complexity - O(1), Space complexity - O(1)
struct minStack2{
    vector<int> vect;
    int minimum;

    void push(int x){
        if(x < minimum){
            vect.push_back(2*x - minimum);
            minimum = x;
        }
        else
            vect.push_back(x);
    }

    int pop(){
        int res;
        int topmost = vect.back();
        vect.pop_back();
        if(topmost <= minimum){
            res = minimum;
            minimum = 2 * minimum - topmost;
            return res;
        } 
        else 
            return topmost;
    }

    int getMin(){
        return minimum;
    }

    int peek(){
        int topmost = vect.back();
        return (topmost <= minimum) ? minimum : topmost;
    }
};

// Infix to Postfix or Infix to Prefix Conversions
// For these conversions precedence and associativity rules are followed
// Precedence of operators - giving lower precedence operator a lower integer
int precedence(char c){
    if(c == '+' || c == '-')
        return 1;
    else if(c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else 
        return -1;
}

// Infix to postfix conversion
// Every item of strings takes constant time 
// So, time complexity - O(n)
string IntoPost(string str){
    stack<char> st;
    string result;
    for(int i = 0; i < str.size(); i++){
        if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^' ){
            while( st.empty() == false && (precedence(st.top()) >= precedence(str[i])) ){
                result += st.top();
                st.pop();
            }
            st.push(str[i]);
        }
        else if(str[i] == '('){
            st.push(str[i]);
        }
        else if(str[i] == ')'){
            while(st.top() != '('){
                result += st.top();
                st.pop();
            }
            st.pop(); // To remove '(' 
        }
        else 
            result+= str[i];
    }
    while(st.empty() == false){
        result+= st.top();
        st.pop();
    }
    return result;
}

// Evaluation of postfix expression
// Input is postfix expression 
int evalPost(string str){
    stack<int> st;
    int num1, num2;
    for(int i = 0; i < str.size(); i++){
        if(isdigit(str[i])){
            st.push(str[i] - '0');
        }
        else if(str[i] != ' '){
            num1 = st.top();
            st.pop();
            num2 = st.top();
            st.pop();

            switch(str[i]){
                case '+' : st.push(num1 + num2);
                        break;
                case '-' : st.push(num1 - num2);
                        break;
                case '*' : st.push(num1 * num2);
                        break;
                case '/' : st.push(num1 / num2);
                        break;
                case '^' : st.push(pow(num1, num2));
                        break;
            }    
        }
    }
    return st.top();
}

// Infix to Prefix Conversion
// Same as postfix conversion, just do the same from right to left
// Gives you the reversed ans so again reverse it
string IntoPre(string str){
    stack<char> st;
    string result, prefix;
    for(int i = str.size() - 1; i >= 0; i--){
        if(str[i] == '+' || str[i] == '-' || str[i] == '/' || str[i] == '*' || str[i] == '^' ){
            while( st.empty() == false && (precedence(st.top()) >= precedence(str[i])) ){
                result += st.top();
                st.pop();
            }
            st.push(str[i]);
        }
        else if(str[i] == ')'){
            st.push(str[i]);
        }
        else if(str[i] == '('){
            while(st.top() != ')'){
                result += st.top();
                st.pop();
            }
            st.pop(); // To remove ')' 
        }
        else 
            result+= str[i];
    }
    while(st.empty() == false){
        result+= st.top();
        st.pop();
    }

    for(int i = result.size() - 1; i >= 0; i--){
        prefix += result[i];
    }
    return prefix;
}

//Evaluation of prefix
// Same as postfix, just travel from right to left
// Check this again
int evalPre(string str){
    stack<int> st;
    int num1, num2;
    for(int i = str.size() - 1; i >= 0; i--){
        if(isdigit(str[i])){
            st.push(str[i] - '0');
        }
        else if(str[i] != ' '){
            num1 = st.top();
            st.pop();
            num2 = st.top();
            st.pop();

            switch(str[i]){
                case '+' : st.push(num1 + num2);
                        break;
                case '-' : st.push(num1 - num2);
                        break;
                case '*' : st.push(num1 * num2);
                        break;
                case '/' : st.push(num1 / num2);
                        break;
                case '^' : st.push(pow(num1, num2));
                        break;
            }    
        }
    }
    return st.top();
}

int main(){
    string str = "(a+b*(c+d))*e";
    cout << IntoPost(str);
    return 0;
}