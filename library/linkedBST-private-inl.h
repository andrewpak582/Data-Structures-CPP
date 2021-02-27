
/**
 * This recursive helper function inserts a key-value pair into a subtree 
 * of the tree, or throws a runtime_error if the key is already present.
 */
template <typename K, typename V>
BSTNode<K,V>*
LinkedBST<K,V>::insertInSubtree(BSTNode<K,V>* current, K key, V value) {
  if (current == NULL){ //if tree is empty create a new node to insert
    //as the root
    size ++;
    return new BSTNode<K,V>(key,value);
  }
  else if (current->key == key) { //should not insert if key is already
    //in the tree
    throw std::runtime_error("Duplicate key.");
  }
  else if (current->key > key) {
    current->left = insertInSubtree(current->left, key, value);
    return current;
  }
  else { //current->key < key
    current->right = insertInSubtree(current->right, key, value);
    return current;
  }
}

/**
 * This recursive helper function updates key-value pair in the subtree 
 * of the tree, or throws a runtime_error if the key is not present.
 */
template <typename K, typename V>
void LinkedBST<K,V>::updateInSubtree(BSTNode<K,V>* current, K key, V value) {
  if (current == NULL){ //cannot update if key is not in tree
    throw std::runtime_error("key is not present to update");
  } else if (current->key == key){ //key is found so update value
    current->value = value;
    return;
  } else if (key < current -> key) { //look for key
    updateInSubtree(current->left, key, value);
  } else { //key > current -> key
    updateInSubtree(current->right, key, value);
  }
}


/**
 * This recursive helper function removes a key-value pair from a subtree 
 * of the tree, or throws a runtime_error if that key was not present.
 *
 * It returns a pointer to the root of the subtree.  This root is often
 * the node that was passed as an argument to the function (current) but
 * might be a different node if current contains the key we are removing
 * from the tree.
 */
template <typename K, typename V>
BSTNode<K,V>* 
LinkedBST<K,V>::removeFromSubtree(BSTNode<K,V>* current, 
                                  K key) {
  if (current == NULL) {
    throw std::runtime_error("LinkedBST::remove called on key not in tree.");
  }

  if (key == current->key) {       // We've found the node to remove
    if ((current -> left == NULL) && (current -> right == NULL)){ //when
      //the node is a leaf
      --size;
      delete current;
      return NULL;
    }
    else if ((current -> left != NULL) && (current -> right == NULL)) {
      //when node only has a left child
      --size;
      BSTNode<K,V>* child = current->left;
      delete current;
      return child;
     }
    else if ((current -> left == NULL) && (current -> right != NULL)) {
      //when node only has a right child
      --size;
      //current->right = current->right->right;
      BSTNode<K,V>* child = current->right;
      delete current;
      return child;
  } else { //when node has both right and left children

    K minNodeKey = getMinInSubtree(current->right);
    V minNodeValue = findInSubtree(current->right, minNodeKey);

    current->key = minNodeKey;
    current->value = minNodeValue;

    current->right = removeFromSubtree(current->right, current->key);
    return current;
  }
}

  if (key < current->key) { //looking for key
    current->left = removeFromSubtree(current->left, key);
  } else { //key > current -> key
    current->right = removeFromSubtree(current->right, key);
  }
  return current;
}


/**
 * Returns true if a key is contained in a subtree of the tree, and
 * false otherwise.
 */
template <typename K, typename V>
bool LinkedBST<K,V>::containsInSubtree(BSTNode<K,V>* current, K key) {
  if (current == NULL){ //key is not contained in subtree
    return false;
  } else if (current -> key == key) { //key is contained in subtree
    return true;
  } else if (key < current -> key) { //looking for key
    return containsInSubtree(current -> left, key);
  } else { //key > current -> key
    return containsInSubtree(current -> right, key);
  }
}


/**
 * Given a key, returns the value for that key from a subtree of the tree.
 * Throws a runtime_error if the key is not in the subtree.
 */
template <typename K, typename V>
V LinkedBST<K,V>::findInSubtree(BSTNode<K,V>* current, K key) {
  if (current == NULL){ //key could not be found
    throw std::runtime_error("could not find key in tree.");
  } else if (key == current -> key) { //key is found
    return current -> value;
  } else if (key < current -> key) { //looking for key
    return findInSubtree(current -> left, key);
  } else { // key > current -> key
    return findInSubtree(current -> right, key);
  }
}


/**
 * Returns the largest key in a subtree of the tree.
 */
template <typename K, typename V>
K LinkedBST<K,V>::getMaxInSubtree(BSTNode<K,V>* current) {
  if (current->right == NULL) {
    return current->key;
  }
  return getMaxInSubtree(current->right);
}


/**
 * Returns the smallest key in a subtree of the tree.
 */
template <typename K, typename V>
K LinkedBST<K,V>::getMinInSubtree(BSTNode<K,V>* current) {
  if (current->left == NULL){ //smallest key is found
    return current->key;
  } 
  return getMinInSubtree(current->left); //looking for smallest key
}


/**
 * Returns the height of a subtree of the tree, or -1 if the subtree
 * is empty.
 */
template <typename K, typename V>
int LinkedBST<K,V>::getHeightOfSubtree(BSTNode<K,V>* current) {
  if (current == NULL){ //subtree is empty
    return -1;
  } 

  int leftTree = getHeightOfSubtree(current->left);
  int rightTree = getHeightOfSubtree(current->right);

  //return the largest subtree height
  if (leftTree > rightTree){
    return ++leftTree;
  }
  else { //leftTree < rightTree
    return ++rightTree;
  }
}

/**
 * Recursively builds a post-order iterator for a subtree of the tree.
 */
template <typename K, typename V>
void LinkedBST<K,V>::buildPostOrder(BSTNode<K,V>* current,
                                       Queue< Pair<K,V> >* it) {
  if (current == NULL) {
    return;
  }
  buildPostOrder(current->left, it);
  buildPostOrder(current->right, it);
  it->enqueue( Pair<K,V>(current->key, current->value) );
}

/**
 * Recursively builds a pre-order iterator for a subtree of the tree.
 */
template <typename K, typename V>
void LinkedBST<K,V>::buildPreOrder(BSTNode<K,V>* current,
                                      Queue< Pair<K,V> >* it) {
  if (current == NULL) {
    return;
  }
  it->enqueue( Pair<K,V>(current->key, current->value) );
  buildPreOrder(current->left, it);
  buildPreOrder(current->right, it);
}


/**
 * Recursively builds an in-order iterator for a subtree of the tree.
 */
template <typename K, typename V>
void LinkedBST<K,V>::buildInOrder(BSTNode<K,V>* current,
                                     Queue< Pair<K,V> >* it) {
  if (current == NULL) {
    return;
  }
  buildInOrder(current->left, it);
  it->enqueue( Pair<K,V>(current->key, current->value) );
  buildInOrder(current->right, it);
}


/**
 * Performs a post-order traversal of the tree, deleting each node from the
 * heap after we have already traversed its children.
 */
template <typename K, typename V>
void LinkedBST<K,V>::traverseAndDelete(BSTNode<K,V>* current) {
  if (current == NULL) {
    return;  //nothing to delete
  }
  //post-order traversal left, then right, then delete current
  traverseAndDelete(current->left);
  traverseAndDelete(current->right);
  delete current;

}



