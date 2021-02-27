#include <stdexcept>
#include <iostream>
#include <fstream>
#include "compareEngine.h"

using namespace std;


CompareEngine::CompareEngine(int phraseSize_, bool useAVL_){
	useAVL = useAVL_;
	phraseSize = phraseSize_;
	allDocs = new AVLTree <string, BST<string, int>*>(); //AVL Tree of BSTs
	priorityQueue = new BinaryHeap <int, Pair<string, string> >();

}

CompareEngine::~CompareEngine(){
	delete priorityQueue;
	List<string>* fileList = this->getFilenames();

	for (int i=0; i<fileList->getSize();i++){ //delete every BST 
		delete allDocs->find(fileList->get(i));
	}

	delete fileList;
	delete allDocs;
}

/* loadDocuments - Load all documents by opening each file listed in filename 
 * and indexing all phrases
 * @param filename - file containing list of essays to index
 * @error throws runtime_error if file fails to open
 */
void CompareEngine::loadDocuments(string filename){
	ifstream infile;
	string oneFile;
	infile.open(filename.c_str());
	if (!infile.is_open()){ //throw error if file fails to open
		throw std::runtime_error("Invalid inputs file.");
		return;
	}
	infile >> oneFile;

	BST<string, int>* bst;
  	while (!infile.eof()){ //load in each document, store phrases in BST, and
  						   //insert each BST into the circularArrayList	
  		bst = loadOneDoc(oneFile);
  		allDocs->insert(oneFile, bst);
  		infile >> oneFile;
  	}

  	infile.close();
}

/* loadOneDoc - indexes an essay using a BST and returns the resulting tree
 * @param filename - file containing the essay to index
 * @return BST<string, int>* pointer to tree indexing the given essay
 * @error throws runtime_error if file does not exist
 * Caller is responsible for deallocating returned BST memory
 */
BST<string, int>* CompareEngine::loadOneDoc(string filename){
	ifstream inFile;
	inFile.open(filename.c_str());
	if (!inFile.is_open()){ //make sure file can be opened
		cerr << "File cannot open." << endl;
		return NULL;
	} else {
		BST<string, int>* BSTDoc;
		//store words in circularArrayList, so can more easily be turned 
		//into phrases
		CircularArrayList<string>* words = new CircularArrayList<string>();
		string word;

		for (int i = 0; i<phraseSize; i++) { //creates array of
			//size phraseSize
			inFile >> word;
			words->insertAtTail(word);
		}
		if (useAVL) { //use AVL tree
			BSTDoc = new AVLTree<string, int>();
		} else { //use LinkedBST tree
			BSTDoc = new LinkedBST<string, int>();
		}

	
		while (!inFile.eof()) {

			string phrase = "";
			for (int i = 0; i < phraseSize; i++) { //creates phrase from array
				phrase = phrase + words->get(i) + " ";
			}

			try { //insert phrase into BST
				BSTDoc->insert(phrase, 1);
			} catch(runtime_error& e) { //udpate value if duplicate key
				BSTDoc->update(phrase, BSTDoc->find(phrase) + 1);
			}
			words->removeHead();
			inFile >> word;
			words->insertAtTail(word);

		}

		inFile.close();
		delete words;
		return BSTDoc;
	}
}

/* getFilenames - returns a list of all of the files indexed by
 * the engine
 * @return List<string>*- a pointer to a unique list containing all of
 *  the files indexed.  Note that this should not point to an internal
 *  private data member; you should create a new List in memory and
 *  return it
 * The caller is responsible for deallocating heap memory related to
 * the List
 */
List<string>* CompareEngine::getFilenames(){
	Queue < Pair <string, BST<string, int>* > >* docQueue = allDocs->getInOrder();
	List<string>* fileNames = new CircularArrayList<string>(); 
	int i=0;
	while (!docQueue->isEmpty()) {
		fileNames->insertAtTail(docQueue->dequeue().first);
		i++;
	}
	delete docQueue;
	return fileNames;
}


 /* removeCommonPhrases - detects phrases common across all essays
  *   and removes them from essays.  
  * @param threshold - the cutoff line for defining a common phrase.  Any
  *          phrase that occurs in a greater fraction of documents
  *          than defined by threshold will be removed.  E.g., a threshold
  *          of 0.10 means any phrase occurring in 10% or more of essays
  *          will be removed
  * @error throws runtime_error if threshold is not between 0 and 1
  */
void CompareEngine::removeCommonPhrases(double threshold) {
	BinaryHeap<int, string>* commonPhrases = new BinaryHeap <int, string>();

	BST<string, int> *allPhrases = new AVLTree<string,int>();
	Queue < Pair <string, BST<string, int>* > >* docQueue = 
					allDocs->getInOrder(); // store a queue of All documents
										   // to extract phrases later

	while (!docQueue->isEmpty()){
		BST<string, int>* docBST = docQueue->dequeue().second;
		Queue < Pair <string, int> >* phraseQueue = 
					docBST->getInOrder(); // make a queue of phrases to store
										  // every phrase
		while (!phraseQueue->isEmpty()){
			try {
				allPhrases->insert(phraseQueue->dequeue().first,0); 
				// insert all elements in phraseQueue into a BST to compare
				// with all other documents
			} catch (std::runtime_error &e) {
				//do nothing
			}
		}
		delete phraseQueue;
	}

	Queue < Pair <string, int> >* allPhraseQueue = allPhrases->getInOrder();
	// store a queue of all common phrases

	while (!allPhraseQueue->isEmpty()){
		string phrase = allPhraseQueue->dequeue().first; // phrase to compare
		Queue < Pair <string, BST<string, int>* > >* docQueue2 = 
					allDocs->getInOrder(); // make a queue of allDocs, to check
					// if the document contains the phrase
		int count = 0;
		while (!docQueue2->isEmpty()){
			BST<string, int>* docQueue2BST = docQueue2->dequeue().second;
			// store the BST that might contain the common phrase
			if (docQueue2BST->contains(phrase)){
				count ++; // if BST contains phrase, increment count
			}
		}
		commonPhrases->insert(-1*count, phrase); // insert into common phrases,
		// our priority queue of counts and phrases.
		delete docQueue2;
	}


	List<string> * filenames = this->getFilenames(); // get a list of filenames
	int currPriority = commonPhrases->getMinPriority(); =
	cout << "Removed Phrases" << endl;
	cout << "---------------" << endl;

	while ((-1.0*currPriority)/(allDocs->getSize()) > threshold){
		string minPhrase = commonPhrases->removeMin();
		for (int i=0; i<filenames->getSize(); i++){ // for all phrases above
			// the threshold, remove them from all documents.
			if (allDocs->find(filenames->get(i))->contains(minPhrase)){
				allDocs->find(filenames->get(i))->remove(minPhrase);

			}
		}
		cout << minPhrase << " , " << -1*currPriority << endl; 
		try { // error should be thrown on empty list
			currPriority = commonPhrases->getMinPriority();
		} catch (std::runtime_error &e) {
			currPriority = 0; // exit while loop if list is empty
		}
	}
	cout << endl;
	delete docQueue;
	delete allPhraseQueue;
	delete allPhrases;
	delete commonPhrases;
	delete filenames;

}

/* plagiarismCases - compares all documents to each other and outputs the
 * highest N number of matches
 */
void CompareEngine::plagiarismCases(){
	List<string>* fileList = this->getFilenames();
	//compare document to all other documents
	for (int i=0; i<fileList->getSize(); i++){
		for (int j=i+1; j<fileList->getSize()-1; j++){
			this->compareTwoDocs(fileList->get(i),fileList->get(j));
		}
	}
	cout << "Plagiarism Cases:" << endl;
	cout << "-----------------" << endl;
	//print out top N highest instances of plagiarism
	for (int i=0; i<fileList->getSize(); i++){
		int hits = -1*priorityQueue->getMinPriority();
		Pair<string, string> docs = priorityQueue->removeMin();
		string doc1 = docs.first;
		string doc2 = docs.second;
		printf("%-18s--- %-19s: %5d hits\n", doc1.c_str(), doc2.c_str(), hits); 
	}
	delete fileList;
}
 
/* compareTwoDocs - uses the trees stored for docA and docB and 
 *                  calculates the number of phrases that match.  
 *                  The result is stored in the scores data membe
 * @param docA, docB - specifies the file names for the two documents
 *                  to compare
 * Returns nothing, but the match is stored in an appropriate class data
 * member
 */
 void CompareEngine::compareTwoDocs(string docA, string docB) {
	BST<string, int>* firstDoc = allDocs->find(docA);
	BST<string, int>* secondDoc = allDocs->find(docB);
	Queue <Pair <string, int> >* firstDocQueue = firstDoc->getInOrder();
	int matchCount = 0;
	while(!firstDocQueue->isEmpty()){
		Pair <string, int> phraseToCompare = firstDocQueue->dequeue();
		if (secondDoc->contains(phraseToCompare.first)){ //if phrase is found
			//in comparedoc
			int secondDocCount = secondDoc->find(phraseToCompare.first);
			if (secondDocCount <= phraseToCompare.second) {
				//store the value of the phrase from compareDoc if it is smaller
				matchCount = matchCount + secondDocCount;
			} else { //store the value of the phrase from firstDoc if it is smaller
				matchCount = matchCount + phraseToCompare.second;
			}
		}
	}
	priorityQueue->insert(-1*matchCount, Pair<string, string>(docA, docB)); 
	delete firstDocQueue;
}

/* outputStats - outputs size and height statistics
*/
void CompareEngine::outputStats(){
	float size = allDocs->getSize();
	float height;
	int maxHeight = 0;
	float totalHeight = 0.0;
	float totalSize = 0.0; 
	float totalRatio = 0.0;
	List<string> * filenames = this->getFilenames();

	for (int i = 0; i<size; i++) { //for each document (BST)
		height = allDocs->find(filenames->get(i))->getHeight(); //get height of each BST
		totalHeight = totalHeight + height;
		float docSize = allDocs->find(filenames->get(i))->getSize(); //get size of each BST
		totalSize = totalSize + docSize;
		totalRatio = totalRatio + ((docSize) / height);
		if (height > maxHeight) { //determine max height
			maxHeight = height;
		}

	}
	cout << "Performance Statistics" << endl;
	cout << "----------------------" << endl;
	cout << endl<< "Max height: " << maxHeight << endl;
	cout << "Average height: " << totalHeight/size << endl;
	cout << "Average size: " << totalSize/size << endl;
	cout << "Average size to height ratio: " << totalRatio/size << endl;

	delete filenames;

}