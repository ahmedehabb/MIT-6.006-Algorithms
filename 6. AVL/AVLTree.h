#include <iostream>
using namespace std; 
#include "Node.h" 


// AVL TREE IS BALANCED BST WHERE EACH NODE ITS BALANCE(LEFT SUBTREE'S HEIGHT - RIGHT SUBTREE HEIGHT)  MUST BE < abs(1) 
// to ensure that the height of the tree is O(logn)
class AvlTree{ 

	Node* root ; 

	//-----------------------------------------------------
	// UTILITY FUNCTIONS ( GET CALLED BY PUBLIC FUNCTIONS ) -> NOT TO EXPOSE OUR ROOT TO THE PUBLIC

	// INSERT OPERATIONS
	// recursive solution there's also an iterative solution for the insertion
	// we will return the newly added node
	// Inserting Node in AVLtree is more complex than BST whyy ??
		// bec we will need to update Height and check balance 
		
	void insertNode(Node*& subroot ,int key){
		
		if(subroot ==nullptr)
		{
			Node* in = new Node(key) ;
			subroot = in ; 

		}else
		{
			if(key < subroot->getValue()){
				
				// very important node (READ)
				//NOTE 1. 
					// by reading the inside of this if statement -> 
					// you will notice we call setHeight() twice (in if and in else)
					// this is because we want to update the height recursively after we put our leaf node
					// so since we want to update it ""AFTER PUTTING LEAF"" we recursevely call insertNode in our case then setheight after it
					// and the setHeight() in else statement is for updating the parent of leaf node only 
					
				// NOTE 2.
					// we will need to check balance of each subroot we passed on from parent of node upto root
					

				if(subroot->getleft())
				{
					Node* left = subroot->getleft();
					insertNode( left, key) ;

					// since we inserted node left to the subroot left we must update subroots height 

					// here i will use ternary operation to check if subroot->getright() exists instead of doing if condition to avoid errors
					// Take care i checked against right only as i'm sure other variable exists 					
					subroot->setHeight( 1 + max(left->getHeight() , !subroot->getright() ? -1 : subroot->getright()->getHeight() ) );

				}else // means no more children in left subtree 
				{
					Node* newNode = new Node(key) ;
					subroot->setLeft(newNode) ;
					newNode->setParent(subroot) ;
					
					// since we inserted node left to the subroot itself we must update subroots height
					
					// here i will use ternary operation to check if subroot->getright() exists instead of doing if condition to avoid errors
					// Take care i checked against right only as i'm sure other variable exists 
					subroot->setHeight( 1 + max(newNode->getHeight() , !subroot->getright() ? -1 : subroot->getright()->getHeight() ) );
				}

			}else if (key > subroot->getValue()){
				
				if(subroot->getright())
				{
					Node* right = subroot->getright();
					insertNode(right , key) ;
				
					// since we inserted node right to the subroot right we must update subroots height
					// doing same ternary operations stuff above
					subroot->setHeight( 1 + max( !subroot->getleft() ? -1 : subroot->getleft()->getHeight() ,right->getHeight() ) );

				}else // means no more children in left subtree 
				{
					Node* newNode = new Node(key) ;
					subroot->setRight(newNode) ;
					newNode->setParent(subroot) ;

					// since we inserted node right to the subroot right we must update subroots height
					// doing same ternary operations stuff above
					subroot->setHeight( 1 + max( !subroot->getleft() ? -1 : subroot->getleft()->getHeight() ,newNode->getHeight() ) );
				}
			}
		
			// this means the subroot exists 
				// we will handle balance of each subroot we pass on 
				// but it must be here at the end so i recursively call untill leaf is put
				// and do balancing when returning from these recursive calls

				// this is made here because no constraints all subroots this function must be called on 
				handleBalance(subroot);
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


	// return height of a certain node : height = length of longest path from a node to the leaves
		//  we assume here leaves are at level 0 ; 
	int heightNode(Node* subRoot){
		if(! subRoot)
			return -1 ;

		return 1 + max(heightNode(subRoot->getleft()), heightNode(subRoot->getright()) );

	}



	// Balance Value !!!
	// this value will be = (left height = right height) = abs(1) if its balanced  
	// as left increase we will "decrement" along 
	// same for right as right subtree height increase we will "Increment" here

	// so if balance =2 or balance = -2 this mean we need to rebalance this node by rotation 

	int getBalance(Node* subroot){

		// we must do right - left as we assumed right->(pos) // left->(neg) ;
		return  ( heightNode(subroot->getright()) - heightNode(subroot->getleft()) ) ;
	}


	// Rotation functions -->

	// take care of order of operations in order not to lose any info 
	void leftRotate(Node* x){
		Node* y= x->getright();
		x->setRight(y->getleft()) ;
		y->setLeft(x);
		// we must also check x's parent so path is correct
		// must also know i'm which child
		if(x->getparent()){
			if(x->getparent()->getleft()==x)
			{
				x->getparent()->setLeft(y);
			}else
				x->getparent()->setRight(y);
		}
	}

	// take care of order of operations in order not to lose any info 
	void RightRotate(Node* y){
		Node* x = y->getleft() ;
		y->setLeft(x->getright()) ;
		x->setRight(y) ;

		// we must also check y's parent so path is correct
		if(y->getparent()){
			// must also know i'm which child
			if(y->getparent()->getleft()==y)
			{
				y->getparent()->setLeft(x);
			}else
				y->getparent()->setRight(x);
		}
	}

	// handling balance when balance be 2 or -2
	void handleBalance(Node* x){

		
		// suppose x is lowest node violating avl 
			// let X is having balance(x) =2 so right(x) is higher 
				//for this case we have 2 inner cases :
					// 1. simple case (1 rotation) 
						//	if(x's right child is right heavy or balanced (balance =1 ) 
						// do left Rotation of (X)
					// 2. double rotations 
						//if x's right child is left heavy so its like zigzag array ( right left  )
						//1.do RightRotation(x->getright()) this gives us the first case (right right ) 
						//2.do LeftRotation(x) 
		
		// and we have 2 other cases for when balance == -2 and left(x) is higher
			
		if(getBalance(x) == 2){ // right(x) is higher 
			
			int rightsBalance = getBalance(x->getright());
			if(rightsBalance == 1 || rightsBalance == 0 ) 
			{
				leftRotate(x);
			}else if(rightsBalance == -1){
				RightRotate(x->getright());
				leftRotate(x);
			}
		}
		else if(getBalance(x) == -2) // left(x) is higher 
		{   // do inversely to upper 

			int leftsBalance = getBalance(x->getleft()) ;
			if(leftsBalance  == -1 || leftsBalance  == 0 )
			{
				RightRotate(x);
			}else if(leftsBalance  == 1){
				leftRotate(x->getleft());
				RightRotate(x);
			}
		}

	}

public:

	AvlTree(){
		root = nullptr;
	}

	AvlTree(Node* myRoot){
		root = myRoot ;
	}

	//Very Important Note ::
		//we made All our functions here call other functions privately as we dont want to expose our root outside the class

	void insert(int key){
		// 2 steps 
			// first one is to insert normally as bst 
			// second one is to fix AVL
		insertNode(root,key);
		
		// we need to fix avl
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

	int findNextLarger(int key){
	
		// steps 
			// 1.  First, if the current node has a right child, move to that right child then, as long as you can see a left child, move to it
			
			// 2. Otherwise (i.e., if the current node has no right child), you need to move up to the parent continuously (so nodes need a right, left and parent pointer) 
		    // until the node you moved from was a left child. 
			// If you get to the root and you still haven't moved up from a left child,your original node was already the highest in the tree.

		Node* found = findKey(key);
		if(found){
			if(found->getright())
			{
				return findMinNode(found->getright())->getValue() ; 
			}else
			{
				while(found->getparent())
				{
					if(found->getparent()->getleft() ==found)
						return found->getparent()->getValue();
					else
						found =found->getparent() ;
				}
			}
		}else
			return NULL ;

	}


	


	//void fixAVL(Node* fixNode){
	//	
	//	// we defined for each node a balance attribute
	//	// balance should be at max abs(1)
	//	// if balance > 1 (positive)
	//		// this mean its right subtree has height more than left 
	//	
	//	// if balance < -1 
	//		// this mean its left subtree has height more than right


	//	if(fixNode->getBalance() > 1){
	//		// here we have 2 case 
	//			// if fixNode right subtree also have balance > 1
	//		if(fixNode->getright() && fixNode->getright()->getBalance() > 1){

	//		}
	//	}
	//}

};