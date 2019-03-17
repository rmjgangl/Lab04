#include <string>
#include <iostream>
#include <queue>
#include "lab4_priority_queue.h"

using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    capacity = n_capacity;
    size = 0;
    heap = new TaskItem* [n_capacity+1];
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    if (size == 0) {
        return true;
    } else
    return false;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    if (size == capacity) {
        return true;
    } else
    return false;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (size == 0) {
        return TaskItem(-1, "NULL");
    } else {
        return *heap[1];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    if (size == capacity) {
        return false;
    }
    if (size == 0) {
        heap[1] = new TaskItem(val);
    } else if (size < capacity) {
        int i = size+1;
        heap[i] = new TaskItem(val);
        while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
            TaskItem* temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
            i /= 2;
        }
    }
    size++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if (size == 0) {
        return false;
    }
    
    int last = size;
    TaskItem* temp = heap[1];
    heap[1] = heap[last];
    heap[last] = temp;
    size--;
    
    if (size == 0) {
        return true;
    } else {
        int i = 1;
        while (i*2 <= size) {
            if (heap[i*2] < heap[i*2+1] && i*2+1 <= size) {
                if (heap[i] < heap[i*2+1]) {
                    TaskItem* temp = heap[i];
                    heap[i] = heap[i*2+1];
                    heap[i*2+1] = temp;
                }
            } else if (heap[i] < heap[i*2] && i*2 <= size) {
                TaskItem* temp = heap[i];
                heap[i] = heap[i*2];
                heap[i*2] = temp;
            }
            i++;
        }
        return true;
    }
    return false;
}
