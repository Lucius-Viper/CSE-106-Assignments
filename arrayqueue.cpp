#include "queue.h"
#include <iostream>
using namespace std;
// Constructor implementation
ArrayQueue::ArrayQueue(int initial_capacity)
{
    // TODO: Initialize data members (data, capacity, front_idx, rear_idx)
    // TODO: Allocate memory for the array with the specified initial capacity
    data = new int[initial_capacity];
    capacity = initial_capacity;
    front_idx = -1;
    rear_idx = -1;
}

// Destructor implementation
ArrayQueue::~ArrayQueue()
{
    // TODO: Free the dynamically allocated memory for the array
    delete[] data;
}

// Enqueue implementation (add an item to the rear of the queue)
void ArrayQueue::enqueue(int item)
{
    // TODO: Check if the array is full
    // TODO: If full, resize the array to double its current capacity
    // TODO: Add the new element to the rear of the queue
    if (front_idx == -1)
    {
        front_idx++;
    }
    else if (((rear_idx + 1) % capacity) == front_idx)
        resize(2 * capacity);

    rear_idx = (rear_idx + 1) % capacity;
    data[rear_idx] = item;
}

// Dequeue implementation (remove an item from the front of the queue)
int ArrayQueue::dequeue()
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Decrement current_size and return the element at the front of the queue
    // TODO: Update front index
    // TODO: Return the dequeued element
    try
    {
        if (empty())
            throw "Cannot Remove From Empty Queue\n";
        int t = data[front_idx];
        if (front_idx == rear_idx)
        {
            clear();
            return t;
        }
        front_idx = (front_idx + 1) % capacity;
        int len = size();
        if (len < capacity / 4 and capacity != 2)
            resize(capacity / 2);
        return t;
    }
    catch (const char *s)
    {
        cout << s << endl;
        return -404 ;
        
    }
}

// Clear implementation
void ArrayQueue::clear()
{
    // TODO: Reset the queue to be empty (reset capacity, front_idx, rear_idx, data)
    delete[] data;
    data = new int[2];
    capacity = 2;
    front_idx = -1;
    rear_idx = -1;
}

// Size implementation
int ArrayQueue::size() const
{
    // TODO: Return the number of elements currently in the queue
    if (front_idx == -1)
        return 0;
    if (front_idx == rear_idx)
        return 1;
    if (front_idx < rear_idx)
        return (rear_idx - front_idx + 1);
    return (capacity - front_idx) + (rear_idx + 1);
}

// Front implementation
int ArrayQueue::front() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the front of the queue without removing it
    try
    {
        if (empty())
            throw "Queue is Empty !\n";
        return data[front_idx];
    }
    catch (const char *s)
    {
        cout << s;
        return -404 ;
    }
}

// Back implementation (get the element at the back of the queue)
int ArrayQueue::back() const
{
    // TODO: Check if the queue is empty, display error message if it is
    // TODO: Return the element at the back of the queue without removing it
    try
    {
        if (empty())
            throw "Queue is Empty !\n";
        return data[rear_idx];
    }
    catch (const char *s)
    {
        cout << s;
        return -404 ;
    }
}

// Empty implementation
bool ArrayQueue::empty() const
{
    // TODO: Return whether the queue is empty (current_size == 0)
    return front_idx == -1;
}

// Print implementation
string ArrayQueue::toString() const
{
    // TODO: Convert queue to a string representation in the format: <elem1, elem2, ..., elemN|
    if (front_idx == -1)
    {
        return string("< |");
    }
    string que;
    que.append("< ");
    int i = front_idx;
    while (i != rear_idx)
    {
        string s;
        s = to_string(data[i]);
        s.append(" ,");
        que.append(s);
        i = (i + 1) % capacity ;
    }
    string s = to_string(data[i]);
    s.append(" |");
    que.append(s);
    return que;
}

// Resize implementation
void ArrayQueue::resize(int new_capacity)
{
    // TODO: Create a new array with the new capacity
    // TODO: Copy elements from the old array to the new array
    // TODO: Delete the old array
    // TODO: Update the data pointer and capacity
    // TODO: Update front and rear indices
    int *temp = new int[new_capacity];

    int i = front_idx, j;
    for (j = 0; j < size(); j++)
    {
        temp[j] = data[i];
        i = (i + 1) % capacity;
    }
    front_idx = 0;
    rear_idx = j - 1;
    delete[] data;
    data = temp;
    capacity = new_capacity;
}

int ArrayQueue::getCapacity() const
{
    // TODO: Return the current capacity of the queue
    return capacity;
}