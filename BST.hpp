#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>

/*
 * Name: Bananannn
 */
template<typename Data>
class BST {

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
      This is inlined because it is trivial.
   */
  BST() : root(nullptr), isize(0) {}


  /** Default destructor.
      Delete every node in this BST.
  */
  ~BST();

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return a pair where the first element is an iterator 
   *  pointing to either the newly inserted element or the element 
   *  that was already in the BST, and the second element is true if the 
   *  element was newly inserted or false if it was already in the BST.
   * 
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=)  
   */
  std::pair<iterator, bool> insert(const Data& item);


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' operator when comparing
   *  Data items. (should not use ==, >, <=, >=).  For the reasoning
   *  behind this, see the assignment writeup.
   */
  iterator find(const Data& item) const;

  
  /** Return the number of items currently in the BST.
   */ 
  unsigned int size() const;
  
  /** Return the height of the BST.
      height of a tree starts with root at height 0
   */ 
  unsigned int height() const;


  /** Return true if the BST is empty, else false.
   */ 
  bool empty() const;

  /** Return an iterator pointing to the first (smallest) item in the BST.
   */ 
  iterator begin() const;

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const;
  /** the helper method of height()
   */ 
  unsigned int heightHelper(BSTNode<Data>* curr) const;


private:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;
  
  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Find the first element of the BST
   * Helper function for the begin method above.
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root);

  /** do a postorder traversal, deleting nodes
   */
  static void deleteAll(BSTNode<Data>* n);

 };

// ********** Function definitions ****************


/** Default destructor.
    Delete every node in this BST.
*/
template <typename Data>
BST<Data>::~BST() {
  deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the
 *  newly inserted
 *  element or the element that was already in the BST, and the second element
 *  is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
  if( isize == 0 ){
    root = new BSTNode<Data>(item);
    isize++;
    return std::pair<BSTIterator<Data>,bool>(BSTIterator<Data>(root),true);
  }
  BSTNode<Data>* current = root;
  // iterate through the tree
  while( current != nullptr ){
    // if the item is smaller than current data
    if( item < current->data ){
      if( current->left != nullptr ){
      // find whether the branch has the even closer one to the value of item
      current = current->left;
      }
      else{
        current->left = new BSTNode<Data>(item);
        current->left->parent = current;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(current->
	left), true);
      }
    }
    // if the item is larger than the current data
    else{
      if( current->right != nullptr ){
        current  = current->right;
      }
      // if the item is smaller than the current one,
      // add to the right 
      else{
        current->right = new BSTNode<Data>(item);
        current->right->parent = current;
        isize++;
        return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(current->
	right), true);
      }
    }
  }    
  // return false if it is already in the tree
  return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(current), false);
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
  // set the initial point to be the root
  BSTNode<Data>* current = root;
  while( current != nullptr ){
    // if the cuurent is the item which we want to find
    if(!(item<(current->data)) && !((current->data)<item)){
      return BSTIterator<Data>(current);
    }
    // traverse through the tree to find the node
    if( item < current->data ){
      current = current->left;
    }
    else{
      current = current->right;
    }
  }
  // return the iterator which point to the object
  return BSTIterator<Data>(current);
}

  
/** Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
  return isize;
}

/** Helper method used to find the height of a tree
 */
template <typename Data>
unsigned int BST<Data>::heightHelper(BSTNode<Data>* curr) const
{
  // base case: if the current node is null, we reach the end
  if( curr == nullptr ){
    return -1;
  }
  // if there are still branches to traverse
  // traverse left and right branches to the end
  unsigned int leftH = 1+heightHelper(curr->left);
  unsigned int rightH = 1+heightHelper(curr->right);
  // return the larger height
  if( leftH < rightH ){
    return rightH;
  }
  else{
    return leftH;
  }
} 
/** Return the height of the BST.
 */

template <typename Data> 
unsigned int BST<Data>::height() const
{
  unsigned int overall = 0;
  BSTNode<Data> * current = root;
  // use helper to find the height of the tree
  if( isize != 0 ){
    overall = heightHelper(current);
  }
  // return 0 if there are no data in the tree
  return overall;

}


/** Return true if the BST is empty, else false.
 */ 
template <typename Data>
bool BST<Data>::empty() const
{
  // if the tree's size is 0, it is empty
  if( isize == 0 ){
    return true;
  }
  // else it is not empty
  return false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
 */ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
  return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
  BSTNode<Data>* current = root;
  while( current != nullptr ){
    current = current->right;
  }
  
  return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
  BSTNode<Data>* current = root;
  while( current->left != nullptr ){
    current = current->left;
  } 
  return current;
}

/** do a postorder traversal, deleting nodes
 */
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n)
{
  if( n == nullptr ){
    return;
  }
  // delete the left branches first
  //n = n->left;
  if( n->left != nullptr ){
    deleteAll(n->left);
  }
  // then delete the right banches 
  //n = n->right;
  if( n->right != nullptr ){
    deleteAll(n->right);
  }
  delete(n);
}
  

#endif //BST_HPP
