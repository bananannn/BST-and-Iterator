#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2017
 * Based on code by Christine Alvarado
 * Add more tests
 */

/* 
 * Name: Bananannn
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);

    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;


    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v.
    unsigned int height = btemp.height();
    if( height != 2 ){
      cout << "Height " << height << " is wrong" << endl;
      return -1;
    }
    else{
      cout << "Height is right" << endl;
    }
    
    // The same as the previous tester but with different tree

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> myv;
    myv.push_back(3);
    myv.push_back(-4);
    myv.push_back(1);
    myv.push_back(-100);
    myv.push_back(-55);
    myv.push_back(23);
    myv.push_back(44);
    myv.push_back(1);

    // Test the template version of the BST  with ints 
    BST<int> mytemp;
    for (int item : myv) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto myp = mytemp.insert(item);
        if (*(myp.first) != item) {
	    cout << "Wrong iterator returned.  "
	         << "Expected " << item << " but got " << *(myp.first) << endl;
	    return -1;
        }
        if (!myp.second) {
	    cout << "Wrong boolean returned.  Expected true but got " 
	         << myp.second << endl;
	    return -1;
        }
    
        cout << "success!" << endl;
	  
    }  

    // Sort the vector, to compare with inorder iteration on the BST
    sort(myv.begin(),myv.end());

    cout << "traversal using iterator..." << endl;
    auto myvit = myv.begin();
    auto myven = myv.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto myen = mytemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto myit = mytemp.begin();
    // iterate through the tree
    for(; myvit != myven; ++myvit) {
        if(! (myit != myen) ) {
            cout << *myit << "," << *myvit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *myit << endl;
        if(*myit != *myvit) {
            cout << *myit << "," << *myvit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++myit;
    }
    // test the size of the tree
    if(mytemp.size() != 8 ){
        cout << "Size is wrong!" << endl;
        return -1;
    }
    else{
        cout << "Size is correct!" << endl;
    }
    
    // test the height of the tree
    unsigned int myheight = mytemp.height();
    if( myheight == 3 ){
        cout << "height is right " << myheight << endl; 
    }
    else{
        cout << "wrong height" << myheight << endl;
        return -1;
    }
    // test on an empty tree
    BST<int> emptyTemp;
    // test the size of the tree
    if(emptyTemp.size() != 0 ){
        cout << "Size is wrong!" << endl;
        return -1;
    }
    else{
        cout << "Size is correct!" << endl;
    }
   
    // test whether the empty function can work properly
    if( emptyTemp.empty() == true ){
        cout << "identify the tree is empty" << endl;
    }
    else{
        cout << "the empty function is wrong" << endl;
        return -1;
    }

    cout << "All tests passed!" << endl;
    return 0;
}
