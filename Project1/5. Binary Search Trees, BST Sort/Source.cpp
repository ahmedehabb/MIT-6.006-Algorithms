#include <iostream>
using namespace std; 


#include"BST.h" 
#include "AugmentedBST.h "


int main() { 

	int keys[] = {49,79,64,83,46,43 };

	BST myBinarySearchTree ;
	AugmentedBST AugmentedBinarySearchTree; 


	 for (int i=0 ; i<6; i++) {
		 myBinarySearchTree.insert(keys[i]);
		 AugmentedBinarySearchTree.insert(keys[i]);
    }
 
	 cout <<myBinarySearchTree.findMin() << endl  ;
	 cout <<myBinarySearchTree.findMax() << endl  ;

	 cout << " ----------------------------------" << endl ;
	 cout << "Augmented BST -- finding sizes of all" << endl ; 
	 cout << AugmentedBinarySearchTree.findSize(49) << endl ;
	 cout << AugmentedBinarySearchTree.findSize(46) << endl ;
	 cout << AugmentedBinarySearchTree.findSize(43) << endl ;
	 cout << AugmentedBinarySearchTree.findSize(79) << endl ;
	 cout << AugmentedBinarySearchTree.findSize(64) << endl ;
	 cout << AugmentedBinarySearchTree.findSize(83) << endl ;


	 cout << "Augmented BST -- finding rank " << endl ; 
	 cout << AugmentedBinarySearchTree.findRank(79) << endl ;

	system("pause");
}