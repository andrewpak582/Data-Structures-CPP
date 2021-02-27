

/* expandCapacity - expands capacity when capacity of Binary Heap has been 
 *					filled.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::expandCapacity() {
	int newCapacity = 2*capacity;
	Pair <P, V> *newItems = new Pair<P, V> [newCapacity];
	for (int i=0; i<size; i++) {
		newItems[i] = items[i];
	}
	delete[ ] items;
	this -> capacity = newCapacity;
	this -> items = newItems; // update the class
}

/* getParent - returns the index integer corresponding parent of current.
 * @param currentPos - index of the current item
 *	return - returns integer index of parent.
 */
template <typename P, typename V>
int BinaryHeap<P,V>::getParent(int currentPos){
	if (currentPos == 0){
		throw std::runtime_error("getParent called on root of tree.");
	}
	return ((currentPos-1)/2);
}

template <typename P, typename V>
int BinaryHeap<P,V>::getLeft(int currentPos){
	//if currentPos has no left, return -1
	if ((2*currentPos) + 1 > size - 1) {
		return -1;
	}
	return ((2*currentPos) + 1);
}

template <typename P, typename V>
int BinaryHeap<P,V>::getRight(int currentPos){
	//if currentPos has no right, return -1
	if ((2*currentPos) + 2 > size -1) {
		return -1;
	}
	return ((2*currentPos) + 2);
}

/* bubbleUp - recursive function that maintains completeness property 
 * 			  while swapping position of currentPos with parent
 *			  until BinaryHeap property is met.
 */
template <typename P, typename V>
void BinaryHeap<P,V>::bubbleUp(int currentPos){
	if (currentPos == 0){ //nothing to bubble up. HeapOrder Property is met
		return;
	} 
	int parentPos = getParent(currentPos);
	if((items[currentPos].first)<(items[parentPos].first)){
		//compare priority of item in currentPos to the priority of the parent
		//item.
		swap(currentPos, parentPos);
		bubbleUp(parentPos);
	} else {
		return;
	}

}


template <typename P, typename V>
void BinaryHeap<P,V>::bubbleDown(int currentPos){
	//if currentPos is leaf, return
	int leftChild = getLeft(currentPos);
	int rightChild = getRight(currentPos);
	int minChild;
	if ((leftChild == -1) && (rightChild == -1)){
		return;
	}
	if ((leftChild != -1) && (rightChild != -1)) {
		minChild = minPriority(leftChild, rightChild); //child with lowest priority
	} else if (rightChild == -1) {
		minChild = leftChild;
	} else {
		minChild = rightChild; // this should never happen
		 					   // because tree should be complete
	}
	if (items[currentPos].first > items[minChild].first) {
		swap(currentPos, minChild);
		bubbleDown(minChild);
	} // swap the thingies and update currentPos
}

template <typename P, typename V>
void BinaryHeap<P,V>::swap(int currentPos, int swapPos){
	Pair<P,V> temp = items[swapPos];
	items[swapPos] = items[currentPos];
	items[currentPos] = temp;
}

template <typename P, typename V>
int BinaryHeap<P,V>::minPriority(int one, int two){
	if (items[one].first > items[two].first){
		return two;
	} else {
		return one;
	}
}