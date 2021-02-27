#include <assert.h>
#include <iostream>
#include <string>
#include "priorityQueue.h"
#include "binaryHeap.h"

using namespace std;

void simpleInsertTest();
void simpleRemoveTest();

int main() {
  // TODO:  Complete this function.
	simpleInsertTest();
	simpleRemoveTest();
}

void simpleInsertTest(){
	BinaryHeap<int, int>* andrew = new BinaryHeap<int, int>();
	assert(andrew->isEmpty());
	assert(andrew->getSize()==0); //testing constructor

	andrew -> insert(2, 2); // test insertion of 1 item
	assert(andrew->getMin() == 2);
	assert(andrew->getMinPriority()==2);
	assert(andrew->getSize()==1);

	andrew -> insert(1, 1); // adding at root of list
	assert(andrew->getMinPriority()==1);
	assert(andrew->getMin() == 1);
	assert(andrew->getSize()==2);

	for (int i=0; i<8; i++){
		andrew -> insert(i+3, i+3);
		assert(andrew->getSize()==i+3);
	}
	assert(andrew->getMinPriority()==1);
	assert(andrew->getMin() == 1);

	andrew->insert(2,2); //check min priority after expandCapacity
	assert(andrew->getSize() == 11);
	assert(andrew->getMin() == 1);
	assert(andrew->getMinPriority()==1);

	andrew->insert(1,2); //check min after duplicate priorities
	assert(andrew->getMinPriority()==1);
	assert(andrew->getSize() == 12);
	assert(!(andrew->isEmpty()));

	andrew->insert(5,5); // test insert in middle of binary heap
	assert(andrew->getMinPriority()==1);
	assert(andrew->getMin()==1);
	assert(andrew->getSize()==13);

	andrew->insert(0,0); // insert at root
	assert(andrew->getMinPriority()==0);
	assert(andrew->getMin()==0);
	assert(andrew->getSize()==14);
	delete andrew;
}

void simpleRemoveTest(){
	BinaryHeap<int, int>* kathy = new BinaryHeap<int, int>();
	assert(kathy->isEmpty());
	try {
		kathy->getMin();
		cout << "getMin should throw error here." << endl;
		assert(false);
	} catch(runtime_error &e){
		//do nothing
	}
	try {
		kathy->removeMin();
		cout << "removeMin should throw error here." << endl;
		assert(false);
	} catch(runtime_error &e){
		//do nothing
	}

	for (int i=0; i<1000; i++){
		kathy->insert(i, i);
	}

	assert(!(kathy->isEmpty()));
	assert(kathy->getMin()==0);
	assert(kathy->getMinPriority()==0);

	kathy->removeMin();
	assert(kathy->getMin()==1);
	assert(kathy->getMinPriority()==1);
	assert(kathy->getSize()==999);

	for (int i=0; i<998; i++){
		kathy->removeMin();
		assert(kathy->getMin()==i+2);
		assert(kathy->getMinPriority()==i+2);
		assert(kathy->getSize()==999-(i+1));
	}
	kathy->removeMin();
	try {
		kathy->getMin();
		cout << "getMin should throw error here." << endl;
		assert(false);
	} catch(runtime_error &e){
		//do nothing
	}
	try {
		kathy->removeMin();
		cout << "removeMin should throw error here." << endl;
		assert(false);
	} catch(runtime_error &e){
		//do nothing
	}
	assert(kathy->isEmpty());
	delete kathy;
}