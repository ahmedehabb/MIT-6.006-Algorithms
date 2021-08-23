#include<iostream>
using namespace std; 
#include<unordered_map>


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
	int count ;
public:
	LinkedList(){
		head= nullptr;
		count = 0 ;
	}

	void insert(T key){
		Node<T>* node = new Node<T>(key);
		if(!head){
			head = node;
			head->setNext(nullptr);
			head->setPrevious(nullptr);
			count ++ ;
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
			count ++ ;
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
			count -- ;
			return ;
		}

		// general case
		//  prev node next(maybe nullptr)
		// remove ^
		previous->setNext(next);
		
		if(next)
			next->setPrevious(previous) ;
		
		count -- ;
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

	int getCount() const{
		return count ; 
	}

	Node<T>* getHead(){
		return head; 
	}

};



// we will treat vertices as if they are indexed 
// so we can use array representation 
	// where its an array of linked list 
	// arr[i] = linked list containing all neighbour of vertex i 

// for simplicity we will let index same as the value of vertex 
// we can make a struct 
// struct vertex { int index; int value; } ;


// root : is vertex where we will assume its level 0 in our search
// adjacency : array of linked lists
void BreadthFirstSearch(LinkedList<int> * adjacency , int root ,unordered_map<int , int> &level, unordered_map<int , int> &parent){
	
	//unordered_map<int , int> level ;  // defined at arguments
	// this hash map will let you save level of each vertex
	// {key->index   : value-> level }

	//unordered_map<int , int> parent ; // defined at arguments
	// this hash map will let you save level of each vertex
	// {key->index of a vertex  : value-> index of its parent }
	

	level[ root ] = 0 ; // since its our root

	int i =1 ;

	vector<int> frontier ;
	frontier.push_back(root);

	while(frontier.size()){

		vector<int> next; // this will save any vertex on next level where i'm
		
		// first loop is considering all vertices in our frontier
		for(int u=0; u< frontier.size() ; u++){

			// looping among all neiighbours of frontier[u] ;
			Node<int>* neighbour = adjacency[ frontier[u]] .getHead();
			
			while(neighbour){	
				// we must check that level we will insert isnt put to avoid infinite loops
					int v = neighbour->getKey();
					// map.find(x)==map.end() -> mean he didnt find x
					if(level.find(v) == level.end())
					{
						level[ v ] = i ;
						parent[ v ] = frontier[u];
						next.push_back(v);
					}
					neighbour = neighbour->getNext() ;
			}
		}
		frontier = next ;
		i+=1 ;
	}
}





int main(){ 


	LinkedList<int> * adjacencyList = new LinkedList<int>[8]; 

	adjacencyList[0].insert(1);
	adjacencyList[0].insert(2);

	adjacencyList[1].insert(0);

	adjacencyList[2].insert(0);
	adjacencyList[2].insert(3);

	adjacencyList[3].insert(2);
	adjacencyList[3].insert(4);
	adjacencyList[3].insert(5);

	adjacencyList[4].insert(3);
	adjacencyList[4].insert(5);
	adjacencyList[4].insert(6);

	adjacencyList[5].insert(3);
	adjacencyList[5].insert(4);
	adjacencyList[5].insert(6);
	adjacencyList[5].insert(7);

	adjacencyList[6].insert(4);
	adjacencyList[6].insert(5);
	adjacencyList[6].insert(7);

	adjacencyList[7].insert(5);
	adjacencyList[7].insert(6);
	


	unordered_map<int , int> level , parent;

	BreadthFirstSearch(adjacencyList,2,level,parent) ;


	for(int i=0 ; i< level.size();i++){
		cout << level.at(i) << endl ;
	}


	
	
	
	int shortestpathfrom_7_till_2 = 1 ;
	// 2 is our root;
	int root = 2; 
	int start = 7;
	cout <<"/////////////////" <<endl 
		<< "path from 7 to 2 " << endl ;
	cout << start << " " ; 
	while(parent[start] != root){
		shortestpathfrom_7_till_2 ++ ;
		start = parent[start] ;
		cout << start << "  " ; 	
	}
	cout << parent[start]  <<endl ;

	cout << "length of shortpath from 7-2 = " << shortestpathfrom_7_till_2 << endl ;
	





	delete [] adjacencyList; 

	system("pause") ;
}