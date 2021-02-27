#ifndef COMPARE_ENGINE_H
#define COMPARE_ENGINE_H

#include "library/circularArrayList.h"
#include "library/pair.h"
#include "priorityQueue.h"
#include "binaryHeap.h"
#include "library/linkedBST.h"
#include "library/AVLTree.h"
#include <string>

using namespace std;


/*Example of typedef.  You do not have to use this, but it can significantly
  simply your declarations.  Instead of saying BST<string, int>, you can
  use DOC.  E.g., to declare a pointer to a BST:
  DOC* essay = new AVLTree<string,int>
*/
  
//typedef BST<string, int> DOC;



/* CompareEngine encapsulates the plagiarism detection task as an object.
 * It loads a set of documents into BST indexes and then allows the user to 
 * do pairwise comparisons to calculate the match between any two essays
 */
class CompareEngine{
  private:
    //TODO: Declare variables here.  You may need to store your files, 
    //essay indexes, match scores...
    string fileList;
    //CircularArrayList< Pair< string, BST<string, int>*> >* allDocs;
    BST<string, BST<string, int>*>* allDocs;
    bool useAVL;
    int phraseSize;
    BinaryHeap<int, Pair<string, string> >* priorityQueue;
    //BinaryHeap<int, string>* commonPhrases;



  public:
    /* ComapreEngine constructor that initializes data members
     * @param phraseSize - number of words in a phrase
     * @param useAVL - true to use AVLTrees for essay indexing, LinkedBST
     *                 otherwise
     */
    CompareEngine(int phraseSize, bool useAVL);
    
    /*Destructor to handle cleaning up internal memory
     */
    ~CompareEngine();
    
    /* Load all documents by opening each file listed in filename and indexing
     *   all phrases
     * @param filename - file containing list of essays to index
     * @error throws runtime_error if file fails to open
     */
    void loadDocuments(string filename);
    
    /* compareTwoDocs - uses the trees stored for docA and docB and 
     *                  calculates the number of phrases that match.  
     *                  The result is stored in the scores data member
     * @param docA, docB - specifies the file names for the two documents
     *                  to compare
     * Returns nothing, but the match is stored in an appropriate class data
     * member
     */
    void compareTwoDocs(string docA, string docB);

    /* getFilenames - returns a list of all of the files indexed by
     * the engine
     * @return List<string>*- a pointer to a unique list containing all of
     *  the files indexed.  Note that this should not point to an internal
     *  private data member; you should create a new List in memory and
     *  return it
     * The caller is responsible for deallocating heap memory related to
     * the List
     */
    List<string>* getFilenames();

    /* removeCommonPhrases - detects phrases common across all essays
     *   and removes them from essays.  
     * @param threshold - the cutoff line for defining a common phrase.  Any
     *          phrase that occurs in a greater fraction of documents
     *          than defined by threshold will be removed.  E.g., a threshold
     *          of 0.10 means any phrase occurring in 10% or more of essays
     *          will be removed
     * @error throws runtime_error if threshold is not between 0 and 1
     */
    void removeCommonPhrases(double threshold);

    /* plagiarismCases - compares all documents to each other and outputs the
     * highest N number of matches
     */
     void plagiarismCases();

    /* outputStats - outputs size and height statistics
     */
     void outputStats();

  private:
    /* Indexes an essay using a BST and returns the resulting tree
     * @param filename - file containing the essay to index
     * @return BST<string, int>* pointer to tree indexing the given essay
     * @error throws runtime_error if file does not exist
     * Caller is responsible for deallocating returned BST memory
     */
    BST<string,int>* loadOneDoc(string filename);
    //using the typedef, this would be:
    //DOC* loadOneDoc(string filename);

    /* TODO: Add additional private methods here */
};
#endif
