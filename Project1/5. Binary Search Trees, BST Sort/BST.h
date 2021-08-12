#include <iostream>
using namespace std; 
#include "Node.h" 

class BST{ 
	Node* root ; 



 
	// recursive solution there's also an iterative solution for the insertion
	void insertNode(Node*& subroot ,int key){

		if(subroot ==nullptr)
		{
			Node* in = new Node(key) ;
			subroot = in ; 
			
		}else
		{
			if(key < subroot->getValue()){
				
				if(subroot->getleft())
				{
					Node* left = subroot->getleft();
					insertNode( left, key) ;
				}else // means no more children in left subtree 
				{
					Node* in = new Node(key) ;
					subroot->setLeft(in) ;
					in->setParent(subroot) ;
					return ; 
				}

			}else if (key > subroot->getValue()){
				
				if(subroot->getright())
				{
					Node* right = subroot->getright();
					insertNode(right , key) ;
				}else // means no more children in left subtree 
				{
					Node* in = new Node(key) ;
					subroot->setRight(in) ;
					in->setParent(subroot) ;
					return ; 
				}

			}
		}
	}




	void inorderTraversal(Node* subroot)
	{
		if (subroot == nullptr) {
			return;
		}
 
		inorderTraversal(subroot->getleft());
		cout << subroot->getValue() << " ";
		inorderTraversal(subroot->getright());
	}

	Node* findMinNode(Node* subroot){
		if(subroot && !subroot->getleft())
			return subroot ;
		else
			return findMinNode(subroot->getleft());
	}

	Node* findMaxNode(Node* subroot){
		if(subroot && !subroot->getright())
			return subroot ;
		else
			return findMaxNode(subroot->getright());
	}

	Node* findKeyNode(Node* subroot, int key){
		
		if(!subroot)
			return nullptr; 

		if(key< subroot->getValue())
		{
			return findKeyNode(subroot->getleft(),key);
		}else if (key > subroot->getValue())
		{
			return findKeyNode(subroot->getright(),key);
		}else
			return subroot ;

	}

public:

	BST(){
		root = nullptr;
	}

	BST(Node* myRoot){
		root = myRoot ;
	}

	//Very Important Note ::
		//we made All our functions here call other functions privately as we dont want to expose our root outside the class

	void insert(int key){
		insertNode(root,key);
	}

	void inorder(){
		inorderTraversal(root);
	}

	int findMin(){
		return findMinNode(root)->getValue();
	}

	int findMax(){
		return findMaxNode(root)->getValue();
	}

	Node* findKey(int key){
		return findKeyNode(root,key);
	}

	//int findNextLarger(int key){
	//			
	//}



};