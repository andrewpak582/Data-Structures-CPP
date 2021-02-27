
/**
 * This recursive helper function inserts a key-value pair into a subtree 
 * of the tree, or throws a runtime_error if the key is already present.
 */
template <typename K, typename V>
AVLTreeNode<K,V>*
AVLTree<K,V>::insertInSubtree(AVLTreeNode<K,V>* current, K key, V value) {
  if (current == NULL){ //if tree is empty create a new node to insert
    //as the root
    size ++;
    return new AVLTreeNode<K,V>(key,value);
  }
  else if (current->key == key) { //should not insert if key is already
    //in the tree
    throw std::runtime_error("Duplicate key.");
  }
  else if (current->key > key) {
    current->left = insertInSubtree(current->left, key, value);
    return balance(current); // balance tree after every insert
  }
  else { //current->key < key
    current->right = insertInSubtree(current->right, key, value);
    return balance(current); // balance tree after every insert
  }
}

/**
 * This recursive helper function updates key-value pair in the subtree 
 * of the tree, or throws a runtime_error if the key is not present.
 */
template <typename K, typename V>
void AVLTree<K,V>::updateInSubtree(AVLTreeNode<K,V>* current, K key, V value) {
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
AVLTreeNode<K,V>* 
AVLTree<K,V>::removeFromSubtree(AVLTreeNode<K,V>* current, 
                                  K key) {
  if (current == NULL) {
    throw std::runtime_error("AVLTree::remove called on key not in tree.");
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
      AVLTreeNode<K,V>* child = current->left;
      delete current;
      return balance(child); // balance the child after remove is called
     }
    else if ((current -> left == NULL) && (current -> right != NULL)) {
      //when node only has a right child
      --size;
      //current->right = current->right->right;
      AVLTreeNode<K,V>* child = current->right;
      delete current;
      return balance(child); // balance the child after remove is called
  } else { //when node has both right and left children

    K minNodeKey = getMinInSubtree(current->right);
    V minNodeValue = findInSubtree(current->right, minNodeKey);

    current->key = minNodeKey;
    current->value = minNodeValue;

    current->right = removeFromSubtree(current->right, current->key);
    return balance(current); // balance the root of the tree
  }
}

  if (key < current->key) { //looking for key
    current->left = removeFromSubtree(current->left, key);
  } else { //key > current -> key
    current->right = removeFromSubtree(current->right, key);
  }
  return balance(current); // balance root after key is removed
}


/**
 * This recursive helper function returns true if a key is contained in 
 * a subtree of the tree, and false otherwise.
 */
template <typename K, typename V>
bool AVLTree<K,V>::containsInSubtree(AVLTreeNode<K,V>* current, K key) {
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
 * Given a key, this recursive helper function returns the value for that 
 * key from a subtree of the tree.
 * Throws a runtime_error if the key is not in the subtree.
 */
template <typename K, typename V>
V AVLTree<K,V>::findInSubtree(AVLTreeNode<K,V>* current, K key) {
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
 * This recursive helper function returns the largest key in a subtree of 
 * the tree.
 */
template <typename K, typename V>
K AVLTree<K,V>::getMaxInSubtree(AVLTreeNode<K,V>* current) {
  if (current->right == NULL) {
    return current->key;
  }
  return getMaxInSubtree(current->right);
}


/**
 * This recursive helper function returns the smallest key in a subtree of 
 * the tree.
 */
template <typename K, typename V>
K AVLTree<K,V>::getMinInSubtree(AVLTreeNode<K,V>* current) {
  if (current->left == NULL){ //smallest key is found
    return current->key;
  } 
  return getMinInSubtree(current->left); //looking for smallest key
}


/**
 * Recursively builds a post-order iterator for a subtree of the tree.
 */
template <typename K, typename V>
void AVLTree<K,V>::buildPostOrder(AVLTreeNode<K,V>* current,
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
void AVLTree<K,V>::buildPreOrder(AVLTreeNode<K,V>* current,
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
void AVLTree<K,V>::buildInOrder(AVLTreeNode<K,V>* current,
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
void AVLTree<K,V>::traverseAndDelete(AVLTreeNode<K,V>* current) {
  if (current == NULL) {
    return;  //nothing to delete
  }
  //post-order traversal left, then right, then delete current
  traverseAndDelete(current->left);
  traverseAndDelete(current->right);
  delete current;

}

/**
 * Given a root of a tree as the paramter, this recursive function balances 
 * the tree building from the most "downstream" imbalance. That is, this 
 * function balances the imbalance that occurs furthest down the tree, working
 * its way up to the current root. Returns a pointer to the root of subtree.
 */
template <typename K, typename V>
AVLTreeNode<K,V>* AVLTree<K,V>::balance(AVLTreeNode<K,V>* current) {
  int leftH;
  int rightH;
  if (current == NULL) { //nothing to balance
    return current;
  }
  computeHeightFromChildren(current); //update current's height
  if (current->left == NULL) {
    leftH = -1; // if left node is NULL, leftH is -1
  } else {
    leftH = current->left->height;
    // update leftH to height of left node
  }
  if (current->right == NULL) {
    rightH = -1; // if right node is NULL, rightH is -1
  } else {
    rightH = current->right->height; 
    // update rightH to height of right node
  }

  if (leftH > rightH +1) { //left subtree is too tall
    int leftLeftH; // left left grandchild
    int leftRightH; // left right grandchild
    if (current->left->left == NULL) {
      leftLeftH = -1; // leftleftH is -1 if left left node is NULL
    } else {
      leftLeftH = current->left->left->height;
    }
    if (current->left->right == NULL) {
      leftRightH = -1; // leftrightH is -1 if left right node is NULL
    } else {
      leftRightH = current->left->right->height;
    }
    if (leftLeftH >= leftRightH) { // left-left imbalance
      return rightRotate(current); //left-outer grandchild is taller
    } else { //left-right imbalance
      return leftRightRotate(current); //left-inner grandchild is taller
    }
  }

  if (rightH > leftH + 1) { //right subtree is too tall
    int rightLeftH;
    int rightRightH;
    if (current->right->left == NULL) { //right left grandchild is NULL
      rightLeftH = -1;
    } else {
      rightLeftH = current->right->left->height;
    }
    if (current->right->right == NULL) { // right right grandchild is NULL
      rightRightH = -1;
    } else {
      rightRightH = current->right->right->height;
    }
    if (rightRightH >= rightLeftH) { // right-right imbalance
      return leftRotate(current);
    } else { //right-left imbalance
      return rightLeftRotate(current);
    }
  }

  return current; //return pointer to root node
}


/**
 * This recursive function returns height of a node by calculating height of 
 * its children (left, right), taking the maxHeight and adding 1.
 */
template <typename K, typename V>
void AVLTree<K,V>::computeHeightFromChildren(AVLTreeNode<K,V>* current) {
  int leftH;
  int rightH ;
  if (current->left == NULL) { 
    leftH = -1; // left child is NULL
  } else {
    leftH = current->left->height;
  }
  if (current->right == NULL) { 
    rightH = -1; // right child is NULL
  } else {
    rightH= current->right->height;
  }

  if (leftH >= rightH) {
    current->height = 1 + leftH; //left height greater than right height
  } else {
    current->height = 1 + rightH; // right height is greater than left height
  }
}

/**
 * rightRotate - performs a right rotate on the current node. The left child
 *               now becomes the new root, and the right child of new root 
 *               becomes left child of old root. Old root now becomes the 
 *               right child of the new root.
 */
template <typename K, typename V>
AVLTreeNode<K,V>*
AVLTree<K,V>::rightRotate(AVLTreeNode<K,V>* current) {
  AVLTreeNode<K,V>* newRoot = current->left; //newRoot is left child of current
  current->left = newRoot->right; // right child of newRoot becomes left child
                                  // of old root.
  newRoot->right = current; // old root becomes right child of newRoot
  computeHeightFromChildren(current); //recompute height of oldRoot
  computeHeightFromChildren(newRoot); //recompute height of new tree
  return newRoot;
}

/**
 * leftRotate - performs a left rotate on the current node. The right child
 *               now becomes the new root, and the left child of new root 
 *               becomes right child of old root. Old root now becomes the 
 *               left child of the new root.
 */
template <typename K, typename V>
AVLTreeNode<K,V>*
AVLTree<K,V>::leftRotate(AVLTreeNode<K,V>* current) {
  AVLTreeNode<K,V>* newRoot = current->right; // newRoot is right child of 
                                              // current
  current->right = newRoot->left; // left child of newRoot becomes right child
                                  // of oldroot
  newRoot->left = current; // oldroot becomes left child of newRoot
  computeHeightFromChildren(current); //recompute height of oldRoot
  computeHeightFromChildren(newRoot); //recompute height of new tree
  return newRoot;
}

/**
 * leftRightRotate - performs a left-right rotate on the current root. 
 *                performs first a leftRotate on the left child and then
 *                a rightRotate on the current root. Returns a pointer to
 *                the new root of the subtree.
 */
template <typename K, typename V>
AVLTreeNode<K,V>*
AVLTree<K,V>::leftRightRotate(AVLTreeNode<K,V>* current) {
  current->left = leftRotate(current->left); // leftRotate left child
  return rightRotate(current); // rightRotate current
}

/**
 * rightLeftRotate - performs a right-left rotate on the current root. 
 *                performs first a rightRotate on the left child of current
 *                and then a leftRotate on current. Returns a pointer to
 *                the new root of the subtree.
 */
template <typename K, typename V>
AVLTreeNode<K,V>*
AVLTree<K,V>::rightLeftRotate(AVLTreeNode<K,V>* current) {
  current->right = rightRotate(current->right); // rightRotate right child
  return leftRotate(current); // leftRotate current
}
