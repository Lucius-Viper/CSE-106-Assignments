#include "queue.h"
#include <iostream>
using namespace std;

// Constructor implementation
ListQueue::ListQueue()
{
    // TODO: Initialize front_node and rear_node
    // TODO: Initialize current_size to 0
    front_node = NULL ;
    rear_node = NULL ;
    current_size = 0 ;
}

// Destructor implementation
ListQueue::~ListQueue()
{
    // TODO: Deallocate all nodes in the linked list
    // TODO: Consider using the clear() method
    clear ();
}

// Enqueue implementation (add an item at the rear of the queue)
void ListQueue::enqueue(int item)
{
    // TODO: Create a new node with the given item
    // TODO: Link the new node to the rear
    // TODO: Update the rear_node
    // TODO: Increment the current size
    Node* temp = new Node(item, NULL);
    if(front_node == NULL ){
        front_node = temp ;
        rear_node = temp ;
        current_size ++ ;
        return ;
    }
    rear_node->next = temp ;
    rear_node = temp ;
    current_size++ ;
    
}

// Dequeue implementation (remove an item from the front of the queue)
int ListQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Store the data from the front node
    // TODO: Update the front pointer to the next node
    // TODO: Update the rear pointer if the queue becomes empty
    // TODO: Delete the old front node
    // TODO: Decrement current_size
    // TODO: Return the stored data
    try {
    if(empty()) throw "Queue is Empty\n";
    int t = front_node->data ;
    Node* temp = front_node ;
    front_node = front_node->next ;
    if(front_node == NULL){rear_node = NULL ;}
    delete temp ;
    current_size -- ;
    return t ;}
    catch(const char* s){
        cout<<s ;
        return -404 ;
    }
}

// Clear implementation (delete all elements)
void ListQueue::clear()
{
    // TODO: Traverse the linked list and delete each node
    // TODO: Reset front and rear pointer
    // TODO: Reset current_size to 0
    Node* temp = front_node ;
    while(front_node != NULL){
        front_node = front_node->next ;
        delete temp ;
        temp = front_node ;
    }
    current_size = 0 ;
    rear_node = NULL ;
}

// Size implementation (return the current number of elements)
int ListQueue::size() const
{
    // TODO: Return the current size (current_size)
    return current_size ;
}

// Front implementation (get the element at the front of the queue)
int ListQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the front node without removing it
    try{
        if(empty())throw"Queue is Empty \n";
        return front_node->data ;
    }
    catch(const char* s){
        cout << s ;
        return -404 ;
    }
}

// Back implementation (get the element at the back of the queue)
int ListQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the data from the back node without removing it
    try{
        if(empty())throw"Queue is Empty \n";
        return rear_node->data ;
    }
    catch(const char* s){
        cout << s ;
        return -404 ;
    }
}

// Empty implementation (check if the queue is empty)
bool ListQueue::empty() const
{
    // TODO: Return whether front is nullptr
    return front_node == NULL ;
}

// Print implementation (print elements from front to rear)
string ListQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    // TODO: Traverse the linked list from front
    Node* temp = front_node ;
    string que("< |") ;
    while(temp != NULL){
        string s = to_string(temp->data);
        if(temp == rear_node)s.append(" |");
        else s.append(" , ");
        que.append(s);
        temp = temp->next ;
    }
    return que ;
    
}
