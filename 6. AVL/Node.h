#include <iostream>
using namespace std; 


class Node{ 
	Node* parent ; 
	Node* left; 
	Node* right ;

	int value ;

	int height; 
	// for leaves height = 0 and all nodes are added initially as leaves
	// as for a leaf node -> height = 1 + maxHeight(left,right) = 1 + -1 = 0 ;
	// since left and right nodes of leaf node are null ptrs and have -1 ;





	

public:
	Node(int key){ 
		parent = nullptr ; // null in default till we set it 
		left = nullptr ; // null in default till we set it 
		right = nullptr ; // null in default till we set it 
		
		value= key ;
		
		height = 0 ;
		// for leaves height = 0 and all nodes are added initially as leaves

	}

	int getHeight(){
		return height ;
	}

	void setHeight(int myHeight){
		height = myHeight;
	}

	int getValue(){
		return value ;
	}

	Node* getleft(){
		return left ;
	}

	Node* getright(){
		return right ;
	}

	Node* getparent(){
		return parent ;
	}

	void setParent(Node* myparent){
		parent = myparent ;
	}

	void setLeft(Node* myLeftChild){
		left = myLeftChild;
	}

	void setRight(Node* myRightChild){
		right = myRightChild ;
	}

};