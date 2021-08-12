#include <iostream>
using namespace std; 
#include "augmentedNode.h"



class AugmentedBST{ 
	AugmentedNode* root ; 

 
	// recursive solution there's also an iterative solution for the insertion
	void insertAugmentedNode(AugmentedNode*& subroot ,int key){

		// in augmented node when inserting whule moving on path to find correct location of node to put it
		// we will increment all nodes we pass on it


		if(subroot ==nullptr)
		{
			AugmentedNode* in = new AugmentedNode(key) ;
			subroot = in ; 
			
		}else
		{
			// incrementing node if it exists and we pass on it
			subroot->incrementSize() ;

			if(key < subroot->getValue()){
				
				if(subroot->getleft())
				{
					AugmentedNode* left = subroot->getleft();
					insertAugmentedNode( left, key) ;
				}else // means no more children in left subtree 
				{
					AugmentedNode* in = new AugmentedNode(key) ;
					subroot->setLeft(in) ;
					in->setParent(subroot) ;
					return ; 
				}

			}else if (key > subroot->getValue()){
				
				if(subroot->getright())
				{
					AugmentedNode* right = subroot->getright();
					insertAugmentedNode(right , key) ;
				}else // means no more children in left subtree 
				{
					AugmentedNode* in = new AugmentedNode(key) ;
					subroot->setRight(in) ;
					in->setParent(subroot) ;
					return ; 
				}

			}
		}
	}




	void inorderTraversal(AugmentedNode* subroot)
	{
		if (subroot == nullptr) {
			return;
		}
 
		inorderTraversal(subroot->getleft());
		cout << subroot->getValue() << " ";
		inorderTraversal(subroot->getright());
	}

	AugmentedNode* findMinAugmentedNode(AugmentedNode* subroot){
		if(subroot && !subroot->getleft())
			return subroot ;
		else
			return findMinAugmentedNode(subroot->getleft());
	}

	AugmentedNode* findMaxAugmentedNode(AugmentedNode* subroot){
		if(subroot && !subroot->getright())
			return subroot ;
		else
			return findMaxAugmentedNode(subroot->getright());
	}

	AugmentedNode* findKeyAugmentedNode(AugmentedNode* subroot, int key){
		
		if(!subroot)
			return nullptr; 

		if(key< subroot->getValue())
		{
			return findKeyAugmentedNode(subroot->getleft(),key);
		}else if (key > subroot->getValue())
		{
			return findKeyAugmentedNode(subroot->getright(),key);
		}else
			return subroot ;

	}

public:

	AugmentedBST(){
		root = nullptr;
	}

	AugmentedBST(AugmentedNode* myRoot){
		root = myRoot ;
	}

	//Very Important Note ::
		//we made All our functions here call other functions privately as we dont want to expose our root outside the class

	void insert(int key){
		insertAugmentedNode(root,key);
	}

	void inorder(){
		inorderTraversal(root);
	}

	int findMin(){
		return findMinAugmentedNode(root)->getValue();
	}

	int findMax(){
		return findMaxAugmentedNode(root)->getValue();
	}

	AugmentedNode* findKey(int key){
		return findKeyAugmentedNode(root,key);
	}

	int findSize(int key){ // return size of a node of value=key 
		AugmentedNode* found = findKey(key) ;
		if(found){
			return found->getSize() ;
		}else
			return -1 ;

	}

	//int findNextLarger(int key){
	//			
	//}



};