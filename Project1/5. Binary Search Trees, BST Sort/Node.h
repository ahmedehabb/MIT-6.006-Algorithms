#include <iostream>
using namespace std; 


class Node{ 
	Node* parent ; 
	Node* left; 
	Node* right ;

	int value ;

public:
	Node(int key){ 
		parent = nullptr ; // null in default till we set it 
		left = nullptr ; // null in default till we set it 
		right = nullptr ; // null in default till we set it 
		value= key ;
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