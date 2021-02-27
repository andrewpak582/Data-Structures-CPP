#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#include <assert.h>

#include "stack.h"
#include "arrayStack.h"

#include "queue.h"
#include "arrayQueue.h"

using namespace std;

 void testPop();
 void testPush();
 void testGetTop();
 void testStackGetSize();
 void testStackIsEmpty();

 void testEnqueue();
 void testDequeue();
 void testQueueGetSize();
 void testQueueIsEmpty();
 void testGetFront();

int main(){
  
  //testing stack first
  testPush();
  testPop();
  testGetTop();
  testStackGetSize();
  testStackIsEmpty();

  //now we can test queue
  testEnqueue();
  testDequeue();
  testQueueIsEmpty();
  testQueueGetSize();
  testGetFront();
  return 0;
}

/* test for pushing items onto a stack
 */
void testPush(){
	Stack<int> * andrew = new ArrayStack<int>();

	andrew->push(1);
	assert(andrew->getTop()==1);
	andrew->push(2);
	assert(andrew->getTop()==2);
	andrew->push(3);
	assert(andrew->getTop()==3);

	//check push works after popping
	andrew->pop();
	andrew->push(4);
	assert(andrew->getTop()==4);

	andrew->push(5);
	andrew->push(6);
	andrew->push(7);
	andrew->push(8);
	andrew->push(9);
	andrew->push(10);
	andrew->push(11);
	andrew->push(12);
	//push enough items to run expandCapacity

	assert(andrew->getTop()==12);
	//see if push works when we expandCapacity

	andrew->push(13);
	assert(andrew->getTop()==13);
	//see if push still works with new expanded list

	cout << "Passed testPush" << endl;
	delete andrew;
}

/* test for poping items onto a stack
 */
void testPop(){
	Stack<int> * andrew = new ArrayStack<int>();
	//cannot pop if no items in list
	try{
    	andrew->pop();
    	assert(0); //fail if get here
 	}catch(runtime_error& e){
    //pass if get here
   		cout << ".";
    	cout.flush();
  	}

	andrew->push(1);
	andrew->pop();

	//cannot pop if no items in list
	if (!andrew->isEmpty()) {
		cout << "list should be empty" << endl;
		cout.flush();
	}

	andrew->push(2);
	andrew->push(3);

	andrew->pop();
	assert(andrew->getTop() == 2);

	for (int i=4; i<15; i++){
		andrew->push(i);
	}

	andrew->pop();
	assert(andrew->getTop()==13);
	//test pop when expanding capacity

	andrew->pop();
	assert(andrew->getTop()==12);
	//test pop when capacity has expanded

	andrew->pop();
	assert(andrew->getTop()==11);
	//test pop when size < 10

	cout << "Passed testPop" << endl;
	delete andrew;

}

/* test for getting the top item of the stack
 */
void testGetTop(){

	Stack<int> *andrew = new ArrayStack<int>();
	//cannot getTop of empty list
	try {
		andrew->getTop();
		assert(0);
	} catch (runtime_error &e) {
		//pass if get here
		cout << "cannot getTop of empty list." << endl;
		cout.flush();
	}

	andrew->push(1);
	assert(andrew->getTop()==1);

	andrew->pop();
	try {
		andrew->getTop();
		assert(0);
	} catch (runtime_error &e) {
		//pass if get here
		cout << "cannot getTop of empty list." << endl;
		cout.flush();
	}

	//test getTop after expand capacity
	for (int i=2; i<12; i++){
		andrew->push(i);
	}
	assert(andrew->getTop()==11);

	andrew->push(12);
	assert(andrew->getTop()==12);

	andrew->push(13);
	assert(andrew->getTop()==13);

	andrew->push(14);
	andrew->pop();
	assert(andrew->getTop()==13);
 
 	//test getTop when size < 10
	andrew->pop();
	andrew->pop();
	assert(andrew->getTop()==11);
	cout << "Passed getTop" << endl;
	delete andrew;
}

/* test for getting the size of the stack
 */
void testStackGetSize(){
	Stack<int> * andrew = new ArrayStack<int>();
	//size = 0 when stack is empty
	assert(andrew->getSize()==0);

	andrew->push(1);
	andrew->pop();
	assert(andrew->getSize()==0); //size = 0 when stack 
	//is empty

	andrew->push(2);
	andrew->push(3);
	assert(andrew->getSize()==2); //getSize when stack is
	//not empty

	andrew->pop();
	assert(andrew->getSize()==1);

	//test getSize after expand capacity
	for (int i=4; i<14; i++) {
		andrew->push(i);
	}
	assert(andrew->getSize()==11);

	andrew->push(14);
	assert(andrew->getSize()==12);

	andrew->pop();
	assert(andrew->getSize()==11);

	//test getSize when size < 10
	andrew->pop();
	andrew->pop();
	assert(andrew->getSize()==9);

	delete andrew;

}

/* test for when stack is empty
 */
void testStackIsEmpty(){
	Stack<int> * andrew = new ArrayStack<int>();
	assert(andrew->isEmpty()); //stack is empty
	//when no items have been added yet

	andrew->push(1);
	if (andrew->isEmpty()){
		cerr << "list should not be empty";
		cout.flush();
	}

	andrew->pop();
	assert(andrew->isEmpty()); 
	//stack is empty after one items has been
	//added and one items has been removed

	for (int i=0; i<12; i++) {
		andrew->push(i);
	}

	andrew->pop();
	if (andrew->isEmpty()){
		cerr << "list should not be empty";
		cout.flush();
	}
	
	//test isEmpty after expanding capacity
	for (int i=0; i<11; i++) {
		andrew->pop();
	}
	assert(andrew->isEmpty());

	cout << "Passed testStackIsEmpty" << endl;

	delete andrew;

}


/* test for adding items to a queue
 */
void testEnqueue(){
	Queue<int> *kathy = new ArrayQueue<int>();
	kathy->enqueue(1);
	assert(kathy->getFront()==1);

	kathy->dequeue();
	kathy->enqueue(2);
	assert(kathy->getFront()==2);
	//test enqueue after dequeuing

	kathy->enqueue(3);
	assert(kathy->getFront()==2);

	kathy->dequeue();
	assert(kathy->getFront()==3);

	//test enqueue after expandCapacity
	for (int i=4; i<14; i++){
		kathy->enqueue(i);
	}
	assert(kathy->getFront()==3);
	assert(kathy->getSize()==11);

	kathy->dequeue();
	kathy->dequeue();
	kathy->enqueue(15);
	assert(kathy->getFront()==5);
	assert(kathy->getSize()==10);

	cout << "Passed testEnqueue" << endl;

	delete kathy;
}

/* test for removing items from the queue
 */
void testDequeue(){
	Queue<int> *kathy = new ArrayQueue<int>();
	//cannot dequeue when no items in queue
	try {
		kathy->dequeue();
		assert(0);
	} catch(runtime_error &e) {
		cout <<"." << endl;
		cout.flush();
	}

	//dequeue when one item in list
	kathy->enqueue(1);
	kathy->dequeue();
	assert(kathy->getSize()==0);
	
	//cannot dequeue when no items in queue
	try {
		kathy->dequeue();
		assert(0);
	} catch(runtime_error &e) {
		cout <<". ." << endl;
		cout.flush();
	}

	//dequeue when multiple items in queue
	kathy->enqueue(2);
	kathy->enqueue(3);
	kathy->dequeue();
	assert(kathy->getFront()==3);

	//test dequeue after expandCapacity
	for (int i=4; i<14; i++) {
		kathy->enqueue(i);
	}
	kathy->dequeue();
	assert(kathy->getFront() == 4);
	assert(kathy->getSize() == 10);

	cout << "Passed testDequeue" << endl;
	delete kathy;
}

/* test for getting the size of the queue
 */
void testQueueGetSize(){
	Queue<int> *kathy = new ArrayQueue<int>();
	//size = 0 when queue is empty
	assert(kathy->getSize()==0);

	//test getSize when one items is added
	kathy->enqueue(1);
	assert(kathy->getSize()==1);

	kathy->dequeue();
	assert(kathy->getSize()==0); //size = 0 when queue 
	//is empty

	//test getSize after expanding capacity
	for (int i=2; i<13; i++) {
		kathy->enqueue(i);
	}
	assert(kathy->getSize()==11);

	kathy->dequeue();
	assert(kathy->getSize()==10);

	for (int i=0; i<10; i++){
		kathy->dequeue();
	}
	assert(kathy->getSize()==0); //size = 0 when queue 
	//is empty

	cout << "Passed testQueueGetSize" << endl;

	delete kathy;
}

/* test for when queue is empty
 */
void testQueueIsEmpty(){
	Queue<int> *kathy = new ArrayQueue<int>();
	assert(kathy->isEmpty()); //queue is empty when
	//no items have been added yet
	
	kathy->enqueue(1);
	if (kathy->isEmpty()){
		cerr << "List should not be empty" << endl;
	}

	kathy->dequeue();
	assert(kathy->isEmpty());
	//queue is empty after one items is added and then
	//removed

	for (int i=2; i<12; i++){
		kathy->enqueue(i);
	}
	if(kathy->isEmpty()){
		cerr << "List should not be empty" << endl;
	}

	//testQueueIsEmpty after expandCapacity
	kathy->enqueue(12);
	if(kathy->isEmpty()){
		cerr << "List should not be empty" << endl;
	}

	kathy->dequeue();
	if(kathy->isEmpty()){
		cerr << "List should not be empty" << endl;
	}

	for (int i=0; i<10; i++) {
		kathy->dequeue();
	}
	assert(kathy->isEmpty());

	cout << "Passed testQueueIsEmpty" << endl;

	delete kathy;
}

/* test for getting the front item of the queue
 */
void testGetFront(){
	Queue<int> *kathy = new ArrayQueue<int>();
	//cannot get front item when queue is empty
	try {
		kathy->getFront();
		assert(0);
	} catch (runtime_error &e) {
		cout << "." << endl;
		cout.flush();
	}

	//get front item when one item in queue
	kathy->enqueue(1);
	assert(kathy->getFront()==1);

	kathy->enqueue(2);
	kathy->dequeue();
	assert(kathy->getFront()==2);
	
	kathy->dequeue();
	//cannot get front item when queue is empty
	try {
		kathy->getFront();
		assert(0);
	} catch (runtime_error &e) {
		cout << ". ." << endl;
		cout.flush();
	}

	//test getFront after expanding capacity
	for (int i=3; i<14; i++) {
		kathy->enqueue(i);
	}
	assert(kathy->getFront()==3);

	kathy->dequeue();
	assert(kathy->getFront()==4);
	for (int i=0; i<10; i++) {
		kathy->dequeue();
	}
	
	//cannot get front item when queue is empty
	try {
		kathy->getFront();
		assert(0);
	} catch (runtime_error &e) {
		cout << ". . ." << endl;
		cout.flush();
	}


	cout << "Passed getFront" << endl;
	delete kathy;
}









