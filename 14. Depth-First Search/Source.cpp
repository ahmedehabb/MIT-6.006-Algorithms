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



void DFS_visit( int vertexS ,LinkedList<int> * adjacency ,vector<int> Vertices, unordered_map<int , int> & parent){
	
	Node<int>* temp =adjacency[vertexS].getHead();		
	for (int i = 0; i < adjacency[vertexS].getCount(); i++)
	{
		if ( parent.find(temp->getKey() ) == parent.end() ){
			parent[temp->getKey()] = vertexS ;
			DFS_visit(temp->getKey() , adjacency ,Vertices , parent ) ;
		}
		temp= temp->getNext() ;
	}
}


// Vertices : contain all vertices by index
// adjacency : array of linked lists
void DepthFirstSearch(LinkedList<int> * adjacency , vector<int> Vertices){
	
	unordered_map<int , int> parent;
	for (int i = 0; i < Vertices.size(); i++)
	{
		// we will see if current vertex v[i] is not saved in parent so itsnot a parent of any node
		if(parent.find(Vertices[i]) == parent.end() ) {
			parent[ Vertices[i] ] = -1 ;
			DFS_visit(Vertices[i], adjacency,Vertices,parent ) ;
		}
	}
}


void DFS_visit_withTrack( int vertexS ,LinkedList<int> * adjacency ,vector<int> Vertices, unordered_map<int , int> & parent,
						  unordered_map<int , int> & trackMap
						 ){
	trackMap[vertexS]=1;
	Node<int>* temp =adjacency[vertexS].getHead();	// all vertices reachable from s 	
	
	for (int i = 0; i < adjacency[vertexS].getCount(); i++)
	{
		if ( parent.find(temp->getKey() ) == parent.end() ){
			parent[temp->getKey()] = vertexS ;
			DFS_visit_withTrack(temp->getKey() , adjacency ,Vertices , parent, trackMap ) ;
		}else{
			//this mean that temp is visited before
			// so we will check if its in the stack or not (ontrack)
			// as if its in stack so thats mean that this is backward edge
			if(trackMap[temp->getKey()] ==1){
				cout << "backwardEdge : " << vertexS << " > " << temp->getKey() <<endl ;
			}

		}
		temp= temp->getNext() ;
	}
	trackMap[vertexS]=0;
}


void DFS_DetectBackwardEdge(LinkedList<int> * adjacency , vector<int> Vertices){
	
	unordered_map<int , int> parent;


	unordered_map<int , int> trackMap; // here we will put trackMap[vertexS]=1 when s is in stack of recursive calls
	// meaning we didnt finish s and we are still exploring 

	for (int i = 0; i < Vertices.size(); i++)
	{
		// we will see if current vertex v[i] is not saved in parent so itsnot a parent of any node
		if(parent.find(Vertices[i]) == parent.end() ) {
			parent[ Vertices[i] ] = -1 ;
			DFS_visit_withTrack(Vertices[i], adjacency,Vertices,parent,trackMap ) ;
		}
	}
}



int main(){ 


	LinkedList<int> * adjacencyList = new LinkedList<int>[8]; 




	// detecting backward edge
	adjacencyList[0].insert(1);
	adjacencyList[1].insert(2);
	adjacencyList[2].insert(3);
	adjacencyList[3].insert(0);



	vector<int> Vertices; 
	for (int i = 0; i < 8; i++)
	{
		Vertices.push_back(i);
	}


	//DepthFirstSearch(adjacencyList,Vertices);
	
	

	// this is same as DetectBackwardEdge but we will save ontrack which will save if the vertex is on stack or not
	DFS_DetectBackwardEdge(adjacencyList,Vertices);
	
	system("pause") ;
}