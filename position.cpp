// Implement the Position class here.
#include <string>
#include <iostream>
#include "position.h"

using namespace std;

Position::Position() {
	x = -1;
	y = -1;
	wall = false;
	path = false;
	visited = false;
	previous = NULL;
}

Position::Position(int inX, int inY) {
	x = inX;
	y = inY;
	wall = false;
	path = false;
	visited = false;
	previous = NULL;
}


int Position::getX(){
	return x;
} 
    
int Position::getY(){
	return y;
}

Position* Position::getPrevious(){
	return 0;
}
bool Position::isVisited(){
	return false;
}         
bool Position::isWall(){
	return false;
}           

/* output a 
 * '1' if it is a wall
 * '*' if it is on the path
 * '0' otherwise
 */
void Position::print(){
	cout << "this has not been implemented yet.";
}

/*Mutator methods, set the given variable to true*/
void Position::setWall(){
	return;
} 
void Position::setVisited(){
	return;
}
void Position::setPath(){
	return;
}
void Position::setX(int newX){
	x = newX;
}
void Position::setY(int newY){
	y = newY;
}

/*Mutator methods*/
void Position::setPrevious(Position* p){
	return;
}

    /*When search is complete, reset all visited and path to false */
void Position::reset(){
	return;
}