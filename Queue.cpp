/*
queue.cpp
*/

#include "queue.h"

Queue::Queue(int maxlen) {
  
    head = 0;
    tail = 0;
    contents=new Location[maxlen];
  
}


Queue::~Queue() {
  
    delete [] contents;
  
}

//Insert a new Location at the end/back of our list
void Queue::add_to_back(Location loc) {

    contents[tail]=loc;
    tail++;

}

//Return and "remove" the oldest Location not already extracted
Location Queue::remove_from_front() {

    head++;
    return contents[head-1];

}

bool Queue::is_empty() {
  
    return head == tail;
  
}

