template<typename T>
class Node{
	T key ;
	Node<T>* previous ;
	Node<T>* next;
	// here we got previous and next so we can delete in O(1) as we will pass node not the key 
	// otherwise we would delete in O(n)
public:
	Node(T myKey,Node<T>* myNext=nullptr,Node<T>* myPrevious=nullptr){
		next=myNext;
		previous=myPrevious;
		key =myKey ;
	}

	void setNext(Node<T>* myNext){
		next =myNext ;
	}

	void setPrevious(Node<T>* myPrevious){
		previous =myPrevious ;
	}

	Node<T>* getNext(){
		return next;
	}

	Node<T>* getPrevious(){
		return previous; 
	}

	T getKey(){
		return key ;
	}

};


template<typename T>
class LinkedList{
	Node<T>* head ;

public:
	LinkedList(){
		head= nullptr;
	}

	void insert(T key){
		Node<T>* node = new Node<T>(key);
		if(!head){
			head = node;
			head->setNext(nullptr);
			head->setPrevious(nullptr);
			return ;
		}else
		{
			// we will insert new nodes in the beginning of the list
			//	Linked List:	head next 
			// ins node here ^	
			head->setPrevious(node) ;
			node->setNext(head) ;
			node->setPrevious(nullptr) ;
			head =node;
		}
	}

	void deleteNode(Node<T>* node){
		if(!node)
			return ;

		Node<T>* previous = node->getPrevious() ;
		Node<T>* next = node->getNext() ;

		// corner case if its first item in list
		// node next
		if(!previous){
			//but must check that there exists next as it could be only item in list
			if(next){
				next->setPrevious(nullptr);
				head = next ;
			}else
			{
				head=nullptr;
			}
			delete []node ;
			return ;
		}

		// general case
		//  prev node next(maybe nullptr)
		// remove ^
		previous->setNext(next);
		
		if(next)
			next->setPrevious(previous) ;
		
		delete []node ;
	}


	Node<T>* search(T key){
		
		if(!head) // list thats empty (could have been initiated then deleted items)
			return nullptr ;

		if(head && head->getKey()== key)
			return head; 

		Node<T>* temp = head->getNext() ;
		
		while(temp){
			if(temp->getKey() == key)
				return temp;
			else
				temp=temp->getNext() ;
		}
	}

	bool isEmpty(){
		// if head=nullptr so empty
		return head==nullptr ;
	}

};


// i implemented Hash table with both division and multiplication methods in same class
// also i assumed that key is int .. it could be whole item for ex 
class HashTable{
	int m ; // m represent size of hash table
	LinkedList<int>* *array ; // this mean array = array of linked list ptrs


public:
	HashTable(int size){
		m=size;
		array= new LinkedList<int>* [m];
		for(int i=0;i<m;i++){
			array[i]= nullptr ; // initializing ptrs as null
		}
	}

	int hash(int key){

		// in division method we avoid certain values of m such as 2^p 
		// as h(k) will be p-lowest bits of k

		// a good choice for m -> prime no. that is away from powers of 2 
		// as for example if we have n=2000
		// so we could do 2000/3 -> 701 why?? 
			// 1.prime away from powers of 2 
			// 2.we dont mind examining average of 3 elements in unsuccessful search )

		return key % m ;
	}

	
	void insert_Division(int key){
		int index = hash(key);

		if( array[index] == nullptr){
			// mean linked list is not initiated 
			array[index]= new LinkedList<int>();	
		}

		array[index]->insert(key);
		return ;
	}

	
	Node<int>* searchKey_Division(int key){
		int index = hash(key);
		if(array[index] == nullptr){
			// mean linked list is not initiated so cant be here
			return nullptr ;
		}

		return array[index]->search(key);

	}

	
	void deleteKey_Division(int key){
		// we must know index to know which linked list 
		int index = hash(key);
		if(array[index] == nullptr){
			// mean linked list is not initiated so cant be here
			return ;
		}
		Node<int>* found  = searchKey_Division(key);
		if(found)
			array[index]->deleteNode(found);
	}

};
