#ifndef MAZE_H_
#define MAZE_H_

#include "position.h"
#include "list.h"

class Maze {
  private:
    int numRows;      // Number of rows in the maze.
    int numColumns;   // Number of columns in the maze.
    Position** grid;  // Maze represented as 2D array of Positions.

  public:
    Maze(int numRows, int numColumns);
    ~Maze();
    
    /* Accessor methods */
    int getRows();            
    int getColumns();

    /* return a pointer to the start location */
    Position* getStart();     

    /* Returns true if p is the exit location */
    bool isExit(Position *p); 
    
    /*Prints the maze and shown in sample output*/
    void print();    

    /* Resets the visited and path information for all Positions in the maze.
     * Wall information remains unchanged */
    void reset();             
                                  
    /* Returns a pointer to a list of the valid neighbors for the given 
     * position. Valid neighbors are within the bounds of the Maze and not 
     * walls.
     * Caller is responsible for freeing the heap-memory for the list.*/
    List<Position*>* getNeighbors(Position* p);

    /* Sets the Position at row, column as a wall.*/
    void setWall(int row, int column); 
    
    /* Outputs the path of Positions between the start of the maze
     * and the exit.  HINT: You will need to begin with the end point
     * and traceback the set of steps that got you to the start location.
     * At each iteration, be sure to set the path variable to true for the
     * current position and add the current position to a data structure 
     * (Stack or Queue?) that stores the path for printing later.
     * If there is no path, throw an exception error since the method should
     * not have been called
     */
    void reportPath(); };

#endif
