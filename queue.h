
#ifndef QUEUE_H
#define QUEUE_H


struct Location {
   int row;
   int col;
};


class Queue {
public: // API:
   
   // constructor. maxlen must be as large as the total number
   // of Locations that will ever be entered into this Queue.
   Queue(int maxlen);
   
   // destructor. releases resources. C++ will call it automatically.
   ~Queue();
   
   // insert a new Location at the end/back of our list   
   void add_to_back(Location loc);

   // return and "remove" the oldest Location not already extracted
   Location remove_from_front();

   // is this Queue empty? (did we extract everything added?)
   bool is_empty();

   // member variables of an Queue, for implementation:
private:
  
   Location* contents; 
   int tail;
   int head; 
            
};

#endif
