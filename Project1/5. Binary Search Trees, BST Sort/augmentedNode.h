#include <iostream>
using namespace std; 


// same as node class but has size in addition
class AugmentedNode{ 

	AugmentedNode* parent ; 
	AugmentedNode* left; 
	AugmentedNode* right ;

	int value ;
	int size ; // this size = #node in tree where i'm its root (by default =1 if'm leave and have no children) ;

public:
	AugmentedNode(int key){ 
		parent = nullptr ; // null in default till we set it 
		left = nullptr ; // null in default till we set it 
		right = nullptr ; // null in default till we set it 
		value= key ;
		size = 1; 
	}

	void incrementSize(){
		size ++ ;
	}

	int getSize(){
		return size;
	}

	int getValue(){
		return value ;
	}

	AugmentedNode* getleft(){
		return left ;
	}

	AugmentedNode* getright(){
		return right ;
	}

	AugmentedNode* getparent(){
		return parent ;
	}

	void setParent(AugmentedNode* myparent){
		parent = myparent ;
	}

	void setLeft(AugmentedNode* myLeftChild){
		left = myLeftChild;
	}

	void setRight(AugmentedNode* myRightChild){
		right = myRightChild ;
	}

};