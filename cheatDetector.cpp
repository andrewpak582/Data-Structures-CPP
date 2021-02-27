#include <iostream>
#include <stdlib.h>
#include "library/list.h"
#include "compareEngine.h"

using namespace std;




int main(int argc, char* argv[]){
  if(argc != 4){
    cerr << "Incorrect number of arguments" << endl;
    cerr << "Usage: cheatDetector file-list phrase-size data-structure";
    cerr << endl;
    return 1;
  }
  //Parse in the command line prompts.
  string fileList = string(argv[1]);
  int phraseSize = atoi(argv[2]);
  bool useAVL = atoi(argv[3]);

  //Create a new cheatDeterctor using CompareEngine class
  CompareEngine *cheatDetector = new CompareEngine(phraseSize, useAVL);

  //Use loadDocuments method on fileList to load all the documents into
  //our cheat detector.
  cheatDetector->loadDocuments(fileList);

  //Use removeCommonPhrases method on our cheat detector to remove all
  //the common phrases in the documents. Removes phrases that occur in 
  //the documents above a pre-set threshold value. The threshold value 
  //is set at a default value of 1. This can be changed by programmer.
  //This method outputs all of the removed phrases, and the time they
  //appear in all documents.
  cheatDetector->removeCommonPhrases(.1);

  // Use plagiarismCases method on our cheat detector to output up to
  // N document pairs, with N equal to the number of files. The 
  // document pairs are sorted by number of matches, with highest
  // matches coming first.
  cheatDetector->plagiarismCases();

  //outputStats outputs the statistics associated to the type of BST
  //used. Computes Max Height, Average Height, Average Size, and 
  //Average size to height ratio.
  cheatDetector->outputStats();

  delete cheatDetector; // free up our data.

}



