#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include "priorityQueue.h"
#include "library/list.h"
#include "library/pair.h"
#include "library/queue.h"

// Forward declaration of the BinaryHeap class
//template <typename P, typename V> class BinaryHeap;

template <typename P, typename V>
class BinaryHeap : public PriorityQueue<P,V> {
  private:
    int size;           // Current number of items in the list.
    int capacity;		// Capacity of list
    Pair <P, V>* items;
    
  public:
 
  	BinaryHeap();
  	~BinaryHeap();

  	/* All public functions declared/detailed in priorityQueue.h*/
    /* These methods are defined in binaryHeap-inl.h*/
        
    /* dictionary operations */
    void insert(P priority, V value);
    V removeMin();    

    /* getter methods */ 
    V getMin();
    P getMinPriority(); 

    /* sizing operations */
   	int getSize();
   	bool isEmpty();  

  private:
  /* Private internal methods that
     * correspond to the public methods defined above.
     * These methods are defined in binaryHeap-private-inl.h
     */ 
     void expandCapacity();
     void bubbleUp(int currentPos);
     void bubbleDown(int currentPos);
     int getParent(int currentPos);
     int getLeft(int currentPos);
     int getRight(int currentPos);
     void swap(int currentPos, int swapPos); // swaps positions of the 
                                             // two parameters
     int minPriority(int one, int two); // returns min value of two parameters
};

#include "binaryHeap-inl.h"
#include "binaryHeap-private-inl.h"

#endif // BINARYHEAP_H_