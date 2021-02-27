#include <stdexcept>
//#include "library/circularArrayList.h" //I don't really think we need need this

/**
 * Standard constructor for the BinaryHeap class.
 *   Constructs an empty BinaryHeap (size 0, with initial capacity = 10).
 */
template <typename P, typename V>
BinaryHeap<P,V>::BinaryHeap() {
  this->size = 0;
  this->capacity = 10;
  this->items = new Pair<P,V>[capacity];
}

template <typename P, typename V>
BinaryHeap<P,V>::~BinaryHeap() {
	delete[] items;
}

template <typename P, typename V>
void BinaryHeap<P,V>::insert(P priority, V value){
	if (size == capacity){
		expandCapacity();
	}
	items[size].first = priority;
	items[size].second = value;
	size ++;
	bubbleUp(size - 1); //(size - 1) is the last element in the list
}

template <typename P, typename V>
V BinaryHeap<P,V>::removeMin(){
	if (isEmpty()){
		throw std::runtime_error("Called removeMin on empty list");
	} 
	V toReturn = items[0].second;
	swap(0, size-1);
	size --;
	bubbleDown(0);
	return toReturn;
}

template <typename P, typename V>
V BinaryHeap<P,V>::getMin(){
	if (isEmpty()){
		throw std::runtime_error("Called getMin on empty list");
	}
	return items[0].second;
}

template <typename P, typename V>
P BinaryHeap<P,V>::getMinPriority(){
	if (isEmpty()){
		throw std::runtime_error("Called getMinPriority on empty list");
	}
	return items[0].first;
}

template <typename P, typename V>
int BinaryHeap<P,V>::getSize(){
	return this->size;
}

template <typename P, typename V>
bool BinaryHeap<P,V>::isEmpty(){
	if (this->size == 0){
		return true;
	} else {
		return false;
	}
}