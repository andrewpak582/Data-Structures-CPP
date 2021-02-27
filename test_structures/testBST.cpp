#include <stdlib.h>  // Used for pseudo-random number generation.
#include <assert.h>  // Used for testing below.

#include "pair.h"
#include "BST.h"
#include "AVLTree.h"
#include "library/circularArrayList.h"
#include "library/queue.h"


void simpleInsertTest();
void simpleUpdateTest();
void insertRemoveTest();
void simpleFindContainsTest();
void simpleGetMinTest();
void traversalOrderTest();
void breakPeoplesRemove();
void dynamicAllocationTest();
void balancedTest();

int main() {
  simpleInsertTest();
  simpleUpdateTest();
  insertRemoveTest();
  simpleFindContainsTest();
  simpleGetMinTest();
  traversalOrderTest();
  dynamicAllocationTest();
  balancedTest();

  return 0;
}



void balancedTest() {
  AVLTree<int,int> AVL;

  assert(AVL.isBalanced());

  for (int i = 0; i < 100; ++i) {
    AVL.insert(2*i + 1, i);
    assert(AVL.isBalanced());
  }
  for (int i=0; i<100; ++i){
    AVL.insert(2*i, i);
    assert(AVL.isBalanced());
  }
  assert(AVL.isBalanced());
  for (int i = 0; i < 100; ++i) {
    AVL.remove(2*i+1);
    assert(AVL.isBalanced());
  }/*
  AVL.remove(3);
  assert(AVL.isBalanced());
  AVL.remove(7);
  assert(AVL.isBalanced());
  AVL.remove(35);
  assert(AVL.isBalanced());
  AVL.remove(1);
  assert(AVL.isBalanced());
  AVL.remove(23);
  assert(AVL.isBalanced());*/
}

/* Follow this template for writing new functions.
 * 1. return type void, no paramters
 * 2. No input/output
 * 3. use asserts to detect failures
 * 4. No memory leaks!
 * 5. Each function should be stand alone i.e., I can copy and paste it
 *    or rename it and it will still work
 * 6. You can create a few long tests or lots of short ones
 */

/* simpleTest - accomplishes the following
 *    *tests getSize
 *    *ensures a new tree is indeed empty
 *    *ensures each insert increases the size by 1
 *    *tests that each inserted element is in the tree
 */
void simpleInsertTest(){
  AVLTree<int,int> AVL;

  assert(AVL.getSize() == 0);  // Checks that initial size is correct.  assert
                               // causes the program to immediately crash if
                               // the condition is false.
  
  for (int i = 0; i < 100; ++i) {
    AVL.insert(2*i + 1, i);
    assert(AVL.getSize() == i+1);
  } 
  for (int i = 0; i < 100; ++i) {
    assert(AVL.find(2*i + 1) == i);
  }
  for (int i = 0; i < 100; ++i) {  // Checks that keys are in the tree.
    assert(AVL.contains(2*i + 1));
  } 
  assert(AVL.getMin()==1);

}


/* simpleUpdateTest - accomplishes the following
 *    *tests update, both when AVL is empty and when it is not empty
 *    *ensures update does not work on empty tree
 *    *ensures size is maintained through update
 *    *tests that each updated element is in the tree
 */
void simpleUpdateTest() {
  AVLTree<int, int> AVL;

  try{
    AVL.update(2,2); // run update on empty tree, should break code
    assert(true == false); //break the code 
  } catch(std::runtime_error& e) {
    //do nothings
  }


  for (int i = 0; i < 100; ++i) {
    AVL.insert(2*i + 1, i);
    assert(AVL.getSize() == i+1);
  } 
  for (int i = 0; i < 100; ++i) {
    AVL.update(2*i + 1, i+1); //update values
  } 
  assert(AVL.getSize()==100); //check if size is maintained
  for (int i = 0; i < 100; ++i) {
    assert(AVL.find(2*i + 1) == i+1); //find updated values
  }
  for (int i = 0; i < 100; ++i) {  // Checks that keys are in the tree.
    assert(AVL.contains(2*i + 1));
  } 
  assert(AVL.getMin()==1); //check if minVal is maintained

  try{ 
    AVL.update(2,2); // run update on empty tree, should break code
    assert(true == false); //break the code 
  } catch(std::runtime_error& e) {
    //do nothings
  }

}

/* insertRemoveTest - accomplishes the following
 *    *tests remove, both when AVL is empty and when it is not empty
 *    *further tests insert, when we remove values along with inserting values
 *    *ensures update does not prevent remove
 *    *ensures remove decreases size by 1
 *    *tests if each removed element is indeed removed from the tree
 *    *tests if we can find elements after remove is called
 */
void insertRemoveTest() {
  AVLTree<int, int> AVL; //initiate a new AVL

  try{
    AVL.remove(0);
    assert(false == true); //break the function
  } catch(std::runtime_error& e){
    //do nothing
  }


  //inserting values
  AVL.insert(15,15);
  AVL.insert(6,6);
  AVL.insert(22,22);
  AVL.insert(9,9);
  AVL.insert(18,18);
  AVL.insert(30,30);
  AVL.insert(17,17);
  assert(AVL.getSize()==7); //check if size is updated

  AVL.remove(17); //remove leaf value
  assert(!AVL.contains(17)); //check if value is removed
  assert(AVL.getSize()==6);
  assert(AVL.contains(18)); //check if other parts of tree are maintained
  assert(AVL.find(18)==18); //check if we can still find other elements in tree
  assert(AVL.contains(6));
  assert(AVL.find(6)==6);

  AVL.insert(17,17); //re-insert leaf
  AVL.update(17,1000); //update value of leaf to test if remove still works
  //These next few tests remove nodes and checks other AVL nodes
  assert(AVL.getSize()==7);
  assert(AVL.contains(15));
  assert(AVL.find(15)==15);
  AVL.remove(15);
  assert(AVL.getSize()==6);
  assert(!AVL.contains(15));
  assert(AVL.contains(17));
  assert(AVL.find(17)==1000);
  assert(AVL.find(17)!=17);
  assert(AVL.contains(6));
  assert(AVL.find(6)==6);
  assert(AVL.contains(22));
  assert(AVL.find(22)==22);
  AVL.remove(6);
  assert(AVL.getSize()==5);
  assert(!AVL.contains(6));
  assert(AVL.contains(9));
  assert(AVL.find(9)==9);

  assert(!AVL.contains(15));
  assert(AVL.contains(22));
  assert(AVL.find(22)==22);
  AVL.remove(22);
  assert(AVL.getSize()==4);
  assert(!AVL.contains(22));
  assert(AVL.contains(9));
  assert(AVL.find(9)==9);
  AVL.remove(9);
  assert(AVL.getSize()==3);
  assert(!AVL.contains(9));
  assert(AVL.contains(18));
  assert(AVL.find(18)==18);
  AVL.remove(18);
  assert(AVL.getSize()==2);
  assert(!AVL.contains(18));
  assert(AVL.contains(30));
  assert(AVL.find(30)==30);
  AVL.remove(30);
  assert(AVL.getSize()==1);
  assert(!AVL.contains(30));
  assert(AVL.contains(17));
  assert(AVL.find(17)==1000);
  AVL.remove(17);
  assert(AVL.getSize()==0);
  assert(!AVL.contains(17));
  
}

/* simpleFindContainsTest - accomplishes the following
 *    *tests find, both when AVL is empty and when it is not empty
 *    *tests contains, both when AVL is empty and when it is not empty
 */
void simpleFindContainsTest() {
  AVLTree<int, int> AVL;

  try {
    AVL.find(0);
    assert(false==true); //error should be thrown when find is called
                         //on empty list
  } catch (std::runtime_error& e){
    //do nothing
  }

  assert(!AVL.contains(0)); //contains is false if list is empty

  //inserting into AVL
  AVL.insert(49,50);
  for (int i=0; i<100; ++i) {
    AVL.insert(2*i,2*i+1);
  }


  //check to see if find/contain works properly
  assert(AVL.find(0) == 1);
  for (int i=0; i<100; ++i) {
    assert(AVL.find(2*i) == 2*i+1);
    assert(AVL.contains(2*i));
  }
  assert(AVL.find(49)==50);
  assert(AVL.contains(49));
}

/* simpleGetMinTest - accomplishes the following
 *    *tests getMin, both when AVL is empty and when it is not empty
 *    *makes sure min key is maintained both when inserting and removing
 *    *ensures update does not affect getMin
 */
void simpleGetMinTest(){
  AVLTree<int, int> AVL;
  assert(AVL.isEmpty()); //AVL should be empty
  try {
    AVL.getMin();
    assert(!AVL.isEmpty());//tests get min when AVL is empty
  } catch (std::runtime_error& e){
    //do nothing
  }

  //testing getMin after inserting
  AVL.insert(15, 15);
  assert(AVL.getMin()==15);
  AVL.insert(30, 30);
  assert(AVL.getMin()==15);

  AVL.insert(7, 7);
  assert(AVL.getMin()==7);

  AVL.insert(21, 21);
  AVL.insert(27, 27);
  AVL.insert(31, 31);
  AVL.insert(29, 29);
  AVL.insert(26, 26);

  assert(AVL.getMin()==7);

  //testing getMin after removing
  AVL.remove(7);
  assert(AVL.getMin()==15);
  AVL.remove(15);
  assert(AVL.getMin()==21);
  assert(AVL.getSize()==6);
  try {
    AVL.find(15); //test find when removing node 15 of AVL
    assert(false == true); //throw error
  }catch(std::runtime_error& e){
    //do nothing
  }
  assert(AVL.find(21)==21);
  assert(AVL.find(26)==26);

  AVL.insert(5, 5);
  AVL.insert(9, 9);
  AVL.insert(8, 8);
  AVL.insert(3, 3);
  AVL.insert(6, 6);
  AVL.insert(4, 4);
  AVL.insert(2, 2);

  assert(AVL.getMin()==2);
  AVL.update(2, 3000); //test that min is maintained after updating value
  assert(AVL.getMin()==2);

  //More tests on getMin after remove
  AVL.remove(5);
  assert(AVL.getMin()==2);
  AVL.remove(3);
  assert(AVL.getMin()==2);
  AVL.remove(2);
  assert(AVL.getMin()==4);
}
/* traversalOrderTest - accomplishes the following
 *    *tests preOrder, postOrder, inOrder, both when AVL is empty and 
 *    *when it is not empty
 *    *ensures traversal order is maintained after inserting and removing
 *    *ensures values associated with key are updated when update is called
 */
void traversalOrderTest(){

  AVLTree<int, int> AVL;
  Queue< Pair<int, int> >* preOrderPre = AVL.getPreOrder();
  try{
    assert(preOrderPre->dequeue().first == 0); //check for preOrder traversal
                                               //on empty AVL
    assert(false == true); //break the function
  } catch(std::runtime_error& e){
    //do nothing
  }

  Queue< Pair<int, int> >* inOrderPre = AVL.getInOrder();
  try{
    assert(inOrderPre->dequeue().first == 0); //check inOrder traversal on
                                              //empty AVL
    assert(false == true); //break the function
  } catch(std::runtime_error& e){
    //do nothing
  }

  //insert values
  AVL.insert(70, 70);
  AVL.insert(40, 40);
  AVL.insert(90, 90);
  AVL.insert(30, 30);
  AVL.insert(50, 50);
  AVL.insert(80, 80);
  AVL.insert(100, 100);
  AVL.insert(20, 20);
  AVL.insert(35, 35);
  AVL.insert(85, 85);

  //check preOrder keys after inserting
  Queue< Pair<int, int> >* preOrder = AVL.getPreOrder();
  assert(preOrder->dequeue().first == 70);
  assert(preOrder->dequeue().first == 40);
  assert(preOrder->dequeue().first == 30);
  assert(preOrder->dequeue().first == 20);
  assert(preOrder->dequeue().first == 35);
  assert(preOrder->dequeue().first == 50);
  assert(preOrder->dequeue().first == 90);
  assert(preOrder->dequeue().first == 80);
  assert(preOrder->dequeue().first == 85);
  assert(preOrder->dequeue().first == 100);

  //check preOrder values after inserting
  Queue< Pair<int, int> >* preOrder2 = AVL.getPreOrder();
  assert(preOrder2->dequeue().second == 70);
  assert(preOrder2->dequeue().second == 40);
  assert(preOrder2->dequeue().second == 30);
  assert(preOrder2->dequeue().second == 20);
  assert(preOrder2->dequeue().second == 35);
  assert(preOrder2->dequeue().second == 50);
  assert(preOrder2->dequeue().second == 90);
  assert(preOrder2->dequeue().second == 80);
  assert(preOrder2->dequeue().second == 85);
  assert(preOrder2->dequeue().second == 100);

  AVL.update(70, 7000);
  AVL.update(30, 3000);
  AVL.update(100, 10000);

  //check preOrder keys after updating values
  Queue< Pair<int, int> >* preOrder20 = AVL.getPreOrder();
  assert(preOrder20->dequeue().second == 7000);
  assert(preOrder20->dequeue().second == 40);
  assert(preOrder20->dequeue().second == 3000);
  assert(preOrder20->dequeue().second == 20);
  assert(preOrder20->dequeue().second == 35);
  assert(preOrder20->dequeue().second == 50);
  assert(preOrder20->dequeue().second == 90);
  assert(preOrder20->dequeue().second == 80);
  assert(preOrder20->dequeue().second == 85);
  assert(preOrder20->dequeue().second == 10000);

  //check postOrder keys
  Queue< Pair<int, int> >* postOrder = AVL.getPostOrder();
  assert(postOrder->dequeue().first == 20);
  assert(postOrder->dequeue().first == 35);
  assert(postOrder->dequeue().first == 30);
  assert(postOrder->dequeue().first == 50);
  assert(postOrder->dequeue().first == 40);
  assert(postOrder->dequeue().first == 85);
  assert(postOrder->dequeue().first == 80);
  assert(postOrder->dequeue().first == 100);
  assert(postOrder->dequeue().first == 90);
  assert(postOrder->dequeue().first == 70);

  //check postOrder values
  Queue< Pair<int, int> >* postOrder2 = AVL.getPostOrder();
  assert(postOrder2->dequeue().second == 20);
  assert(postOrder2->dequeue().second == 35);
  assert(postOrder2->dequeue().second == 3000);
  assert(postOrder2->dequeue().second == 50);
  assert(postOrder2->dequeue().second == 40);
  assert(postOrder2->dequeue().second == 85);
  assert(postOrder2->dequeue().second == 80);
  assert(postOrder2->dequeue().second == 10000);
  assert(postOrder2->dequeue().second == 90);
  assert(postOrder2->dequeue().second == 7000);

  AVL.update(70, 70);
  AVL.update(30, 30);
  AVL.update(100, 100);

  //check postOrder values after updating back
  Queue< Pair<int, int> >* postOrder20 = AVL.getPostOrder();
  assert(postOrder20->dequeue().second == 20);
  assert(postOrder20->dequeue().second == 35);
  assert(postOrder20->dequeue().second == 30);
  assert(postOrder20->dequeue().second == 50);
  assert(postOrder20->dequeue().second == 40);
  assert(postOrder20->dequeue().second == 85);
  assert(postOrder20->dequeue().second == 80);
  assert(postOrder20->dequeue().second == 100);
  assert(postOrder20->dequeue().second == 90);
  assert(postOrder20->dequeue().second == 70);

  //check inOrder keys
  Queue< Pair<int, int> >* inOrder = AVL.getInOrder();
  assert(inOrder->dequeue().first == 20);
  assert(inOrder->dequeue().first == 30);
  assert(inOrder->dequeue().first == 35);
  assert(inOrder->dequeue().first == 40);
  assert(inOrder->dequeue().first == 50);
  assert(inOrder->dequeue().first == 70);
  assert(inOrder->dequeue().first == 80);
  assert(inOrder->dequeue().first == 85);
  assert(inOrder->dequeue().first == 90);
  assert(inOrder->dequeue().first == 100);

  //check inOrder values
  Queue< Pair<int, int> >* inOrder2 = AVL.getInOrder();
  assert(inOrder2->dequeue().second == 20);
  assert(inOrder2->dequeue().second == 30);
  assert(inOrder2->dequeue().second == 35);
  assert(inOrder2->dequeue().second == 40);
  assert(inOrder2->dequeue().second == 50);
  assert(inOrder2->dequeue().second == 70);
  assert(inOrder2->dequeue().second == 80);
  assert(inOrder2->dequeue().second == 85);
  assert(inOrder2->dequeue().second == 90);
  assert(inOrder2->dequeue().second == 100);

  AVL.update(70,70000);
  AVL.update(30, 30000);
  AVL.update(100, 100000);
  Queue< Pair<int, int> >* inOrder20 = AVL.getInOrder();
  assert(inOrder20->dequeue().second == 20);
  assert(inOrder20->dequeue().second == 30000);
  assert(inOrder20->dequeue().second == 35);
  assert(inOrder20->dequeue().second == 40);
  assert(inOrder20->dequeue().second == 50);
  assert(inOrder20->dequeue().second == 70000);
  assert(inOrder20->dequeue().second == 80);
  assert(inOrder20->dequeue().second == 85);
  assert(inOrder20->dequeue().second == 90);
  assert(inOrder20->dequeue().second == 100000);

  AVL.insert(65, 65);
  AVL.insert(33, 33);

  //check if preOrder traversal is maintained with extra inserts
  Queue< Pair<int, int> >* preOrder3 = AVL.getPreOrder();
  assert(preOrder3->dequeue().first == 70);
  assert(preOrder3->dequeue().first == 40);
  assert(preOrder3->dequeue().first == 30);
  assert(preOrder3->dequeue().first == 20);
  assert(preOrder3->dequeue().first == 35);
  assert(preOrder3->dequeue().first == 33);
  assert(preOrder3->dequeue().first == 50);
  assert(preOrder3->dequeue().first == 65);
  assert(preOrder3->dequeue().first == 90);
  assert(preOrder3->dequeue().first == 80);
  assert(preOrder3->dequeue().first == 85);
  assert(preOrder3->dequeue().first == 100);

  //check if inOrder traversal is maintained with extra inserts
  Queue< Pair<int, int> >* inOrder3 = AVL.getInOrder();
  assert(inOrder3->dequeue().first == 20);
  assert(inOrder3->dequeue().first == 30);
  assert(inOrder3->dequeue().first == 33);
  assert(inOrder3->dequeue().first == 35);
  assert(inOrder3->dequeue().first == 40);
  assert(inOrder3->dequeue().first == 50);
  assert(inOrder3->dequeue().first == 65);
  assert(inOrder3->dequeue().first == 70);
  assert(inOrder3->dequeue().first == 80);
  assert(inOrder3->dequeue().first == 85);
  assert(inOrder3->dequeue().first == 90);
  assert(inOrder3->dequeue().first == 100);
  /* commenting out remove, as balance messes up order of traversal
  //AVL.remove(70);
  //check if preOrder traversal is maintained when removing root
  Queue< Pair<int, int> >* preOrder4 = AVL.getPreOrder();
  assert(preOrder4->dequeue().first == 80);
  assert(preOrder4->dequeue().first == 40);
  assert(preOrder4->dequeue().first == 30);
  assert(preOrder4->dequeue().first == 20);
  assert(preOrder4->dequeue().first == 35);
  assert(preOrder4->dequeue().first == 33);
  assert(preOrder4->dequeue().first == 50);
  assert(preOrder4->dequeue().first == 65);
  assert(preOrder4->dequeue().first == 90);
  assert(preOrder4->dequeue().first == 85);
  assert(preOrder4->dequeue().first == 100);

  //check if inOrder traversal is maintained when removing root
  Queue< Pair<int, int> >* inOrder4 = AVL.getInOrder();
  assert(inOrder4->dequeue().first == 20);
  assert(inOrder4->dequeue().first == 30);
  assert(inOrder4->dequeue().first == 33);
  assert(inOrder4->dequeue().first == 35);
  assert(inOrder4->dequeue().first == 40);
  assert(inOrder4->dequeue().first == 50);
  assert(inOrder4->dequeue().first == 65);
  assert(inOrder4->dequeue().first == 80);
  assert(inOrder4->dequeue().first == 85);
  assert(inOrder4->dequeue().first == 90);
  assert(inOrder4->dequeue().first == 100);
*/
  delete inOrderPre;
  delete inOrder;
  delete inOrder2;
  delete inOrder3;
  delete preOrderPre;
  delete preOrder;
  delete preOrder2;
  delete preOrder3;
  delete postOrder;
  delete postOrder2;
  delete preOrder20;
  delete postOrder20;
  delete inOrder20;
}

/**
 * dynamicAllocationTest - test to check if destructor of AVL trees work
 *                         on a non-empty list.
 */
void dynamicAllocationTest(){
  AVLTree<int, int>* AVL = new AVLTree<int,int>();
  AVL->insert(7,7);

  delete AVL;
}
