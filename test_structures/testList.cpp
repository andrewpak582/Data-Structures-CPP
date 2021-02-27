#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

#include <assert.h>

#include "list.h"
#include "circularArrayList.h"

using namespace std;

void testInsertGet();
void testExpandCapacity();

int main(){

  testInsertGet();
  testExpandCapacity();
}

/* A simple test for adding a few items and verifying the were placed in
 * the list*/
void testInsertGet(){
  List<string> * list = new CircularArrayList<string>();

  cout << "Test Insert/Get: ";

  list->insertAtHead("a");
  assert(list->get(0) == "a");
  cout << ".";
  cout.flush();

  list->insertAtHead("b");
  assert(list->get(0) == "b");
  cout << ".";
  cout.flush();

  assert(list->get(1) == "a");
  cout << ".";
  cout.flush();
  
  list->insertAtTail("c");
  assert(list->get(2) == "c");
  cout << ".";
  cout.flush();

  list->insertAtTail("d");
  assert(list->get(3) == "d");
  assert(list->get(2) == "c");
  assert(list->get(1) == "a");
  cout << ".";
  cout.flush();

  /* out of bounds get test*/
  try{
    list->get(list->getSize());
    assert(0); //fail if get here
  }catch(runtime_error& e){
    //pass if get here
    cout << ".";
    cout.flush();
  }

  try{
    list->get(-1);
    assert(0); //fail if get here
  }catch(runtime_error& e){
    //pass if get here
    cout << ".";
    cout.flush();
  }


  
  delete list;

  cout << " PASS" << endl;
}

/* test to make sure expand capacity works after inserting 
 * and removing items
 */
void testExpandCapacity(){
  List<int> * list = new CircularArrayList<int>();
  cout << "Test Expanding: ";
  cout.flush();
  //test expand capacity when inserting many items
  for(int i = 0; i < 100; i++){
    list->insertAtTail(i);
  }
  cout << "Inserting 100 items";
  cout.flush();
  for(int i=0; i<50; i++) {
    list->removeTail();
  }
  cout << " Deleting 50 items" << endl;
  cout.flush();
  for(int i=0; i<70; i++) {
    list->insertAtTail(i);
  }

  //test expand capacity after deleteing and then
  //inserting many items
  cout << "Inserting 70 more items";
  cout.flush();
  assert(list->peekHead()==0);
  assert(list->getSize() == 120);
  cout << " PASS" << endl;
  
  
  delete list;
  
  //make sure head position is still maintained
  //after expanding capacity through inserting
  //at head
  list = new CircularArrayList<int>();
  cout << "More testing: ";
  for(int i=0; i<10; i++){
    list->insertAtTail(i);
  }
  list->insertAtHead(10); //10th index
  cout << "Inserting 10 at head" << endl;
  cout.flush();
  assert(list->peekHead()== 10);
  assert(list->get(0) == 10);
  for (int i=1; i<list->getSize(); i++){
    assert(list->get(i) == i-1); //make sure other 
    //indices are also maintained
  }
  cout << " PASS retain insertHead index" << endl;
  
  delete list;

  //make sure head position is still maintained
  //after removing head and expanding capacity

  list = new CircularArrayList<int>();
  cout << "More testing on new list: ";
  for (int i=0; i<10; i++) {
    list->insertAtTail(i);
  }

  list->removeHead();
  list->removeHead();
  assert(list->peekHead() == 2);
  list->insertAtTail(100);
  assert(list->peekHead() == 2);
  list->insertAtTail(100);
  list->insertAtTail(100); //expand capacity
  assert(list->peekHead() == 2); //make sure
  //head position is maintained
  assert(list->get(3)==5); //make sure other indices
  //are also maintained
  assert(list->get(4)==6);
  assert(list->get(10) == 100);
  assert(list->getSize() == 11);
 
  cout << " PASS retain removeHead index" << endl;
 
  delete list;

  list = new CircularArrayList<int>();
  for (int i=0; i<50; i++){
    list->insertAtTail(i); // adding 50 items to empty array
  }
  int i=1;
  assert(list->get(i+5) == i+5); // checking if an arbitrary index was
  //maintained when expand capacity was called.
  assert(list->peekHead() == 0); // checking headPos

  list->removeHead();
  assert(list->peekHead() == 1); // checking headPos after removeHead

  list -> insertAtHead(0);
  assert(list->peekHead() == 0);
  assert(list->peekTail() == 49);

  delete list;

  list = new CircularArrayList<int>();
  for (int i=0; i<10; i++) {
    list->insertAtHead(i); // inserting 10 items int empty array
  }

  list->insertAtTail(10); // expandCapacity is called
  assert(list->peekHead()==9); // check headPos is maintained
  assert(list->peekTail()==10);
  assert(list->get(0) == 9);
  assert(list->get(1) == 8);
  assert(list->get(10) == 10);
  for (int i=0; i<10; i++) {
    assert(list->get(i) == 9-i); // check if list indexes were all maintained
  }
  delete list;

  /* 
   * These next few tests test for the same things, just different variations
   * of them. I.E. inserting at tail as opposed to head to expandCapacity
   * and vice versa.
   */

  list = new CircularArrayList<int>();
  for (int i=0; i<10; i++) {
    list->insertAtHead(i);
  }

  list->insertAtHead(10);
  assert(list->peekHead()==10);
  assert(list->peekTail()==0);
  for (int i=0; i<11; i++) {
    assert(list->get(i) == 10-i);
  }
  delete list;

  list = new CircularArrayList<int>();
  for (int i=0; i<10; i++) {
    list->insertAtTail(i);
  }

  list->insertAtTail(10);
  assert(list->peekHead()==0);
  for (int i=0; i<11; i++) {
    assert(list->get(i) == i);
  }
  delete list;

  list = new CircularArrayList<int>();
  for (int i=0; i<10; i++) {
    list->insertAtTail(i);
  }

  list->insertAtHead(10);
  assert(list->peekHead()==10);
  for (int i=1; i<11; i++) {
    assert(list->get(i) == i-1);
  }
  delete list;

  list = new CircularArrayList<int>();
  list -> insertAtTail(2);
  list -> insertAtTail(3);
  list -> insertAtTail(4);
  list -> insertAtHead(1);
  list -> insertAtTail(5);
  list -> insertAtHead(0);
  list -> insertAtTail(6);
  list -> insertAtTail(7);
  list -> insertAtTail(8);
  list -> insertAtTail(9);
  //expand capacity
  list -> insertAtTail(10);
  //check indexing
  for (int i = 0; i<11; i++) {
    assert(list->get(i) == i);
  }
  delete list;
  cout << "Passed testExpandCapacity" << endl;

}



