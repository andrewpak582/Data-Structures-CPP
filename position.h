#ifndef POSITION_H_
#define POSITION_H_

class Position {
  private:
    //Stores the row and column
    int x;                
    int y;             

    //Stores whether the position is a wall
    bool wall;             

    //For use in search: set whether the current location has
    //  already been visited; whether it is in the path; a pointer
    //  to the previous location in the search
    bool visited;           
    bool path;             
    Position* previous;   


  public:
    /* Constructors: default constructor sets location to (-1,-1)*/
    Position();   
    Position(int inX, int inY);

    /*Accessor methods*/
    int getX();     
    int getY();  

    Position* getPrevious();      
    bool isVisited();            
    bool isWall();              

    /* output a 
     * '1' if it is a wall
     * '*' if it is on the path
     * '0' otherwise
     */
    void print();

    /*Mutator methods, set the given variable to true*/
    void setWall();   
    void setVisited();  
    void setPath(); 
    void setX(int newX);
    void setY(int newY);

    /*Mutator methods*/
    void setPrevious(Position* p); 

    /*When search is complete, reset all visited and path to false */
    void reset();          
};

#endif
