#include<iostream>
#include<unordered_map>
#include <vector>
#include <string>
using namespace std; 

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


LinkedList<vector<int>>  handleNeighbours(vector<vector<char>>& maze, vector<int>& entrance,unordered_map<int,bool>& visited,bool &border){

	// this bool border will change it to 1 -> mean we found a border element and you should finish
	// no need to continue finding other neighbours

	LinkedList< vector<int> > adjacencyList ; // we will save [row,col] as an element 
	vector<int> x;	

	if( (visited[ (entrance[0]-1)*10 + entrance[1] ]==0) && // inorder not to get back
		entrance[0]>0 && maze[entrance[0]-1][entrance[1]]=='.'){ // mean it can have upper child

		x.push_back(entrance[0]-1);
		x.push_back(entrance[1]);
		adjacencyList.insert(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	if( (visited[ (entrance[0]+1)*10 + entrance[1] ]==0) && // inorder not to get back
		entrance[0]< maze.size()-1 && maze[entrance[0]+1][entrance[1]]=='.'){ // mean it can have lower child
		x.push_back(entrance[0]+1);
		x.push_back(entrance[1]);
		adjacencyList.insert(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}
	
	if( (visited[ (entrance[0])*10 + (entrance[1]-1) ]==0) && // inorder not to get back
		entrance[1]>0 && maze[entrance[0]][entrance[1]-1]=='.'){ // mean it can have left child
		x.push_back(entrance[0]);
		x.push_back(entrance[1]-1);
		adjacencyList.insert(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	if( (visited[ (entrance[0])*10 + entrance[1]+1 ]==0) && // inorder not to get back
		entrance[1]<maze[0].size()-1 && maze[entrance[0]][entrance[1]+1]=='.'){ // mean it can have right child
		x.push_back(entrance[0]);
		x.push_back(entrance[1]+1);
		adjacencyList.insert(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	return adjacencyList;

}


	
int Solve(vector<vector<char>>& maze, vector<int> entrance,	unordered_map<int,bool>& visited,int level ,int &minpath) {

	// we must keep track of previous visited node in order not to enter infinite loop

	// first thing we will make is adjacency list 
	// our neighbours will be only those around us in matrix and must be reachable

	// ex :    + . . + +
	//         + + . + +
	//	       . + . + +
	
	// and you entered at 0,1 first row 2nd column -> so you will hav eonly 1 neighbour -> at (0,2)

	// our adjacency List will only be one linked list and will be updated as we go 
	// we dont need to get all possible neighbours of each point 
	

		/*
		[["+",".","+","+","+","+","+"],
			["+",".","+",".",".",".","+"],
			["+",".","+",".","+",".","+"],
			["+",".",".",".","+",".","+"],
			["+","+","+","+","+",".","+"]]*/
	
	
	// if its entrance will be [1 0] -> so will take number 10 in hash table
	visited[entrance[0]*10+entrance[1]]=1 ;

	// border rows/ cols
	if(level!=0 && ( entrance[0]==0 || entrance[0]==maze.size()-1 || entrance[1]==0 || entrance[1]==maze[0].size()-1 ) ){
		visited[entrance[0]*10+entrance[1]]=0 ;
		return level;
	}
	bool border =0 ;

	

	LinkedList<vector<int>> adjacency =	handleNeighbours(maze,entrance,visited,border);


	if(border && level+1 <minpath ){
		
		// unchecking the visited element in maze 
		// as it could be used in getting another path that could be better
		// without uncheking it at end --> you say that you will use it only once
		visited[entrance[0]*10+entrance[1]]=0 ;

		minpath= level+1;
		return minpath;
	}

	Node<vector<int>>* temp = adjacency.getHead();
	for(int i=0;i<adjacency.getCount(); i++){
		//entrance = temp->getKey() ; 

		// will pass last visited as my current entrance
		// and new entrance will be temp->getkey as it is the neighbour 
		Solve(maze,temp->getKey(),visited,level+1,minpath );

		temp=temp->getNext();
	}
	
	

	// There are tricky part here which is -->
		// unchecking the visited element in maze 
		// as it could be used in getting another path that could be better
		// without uncheking it at end --> you say that you will use it only once
	visited[entrance[0]*10+entrance[1]]=0 ;

	if(minpath==INT_MAX)
		return -1;

	return minpath;
}


int main(){ 


	/*
	Problem Defintition -->

	You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls (represented as '+'). 

	You are also given the entrance of the maze, where entrance = [entrancerow, entrancecol] denotes the row and column 
	of the cell you are initially standing at.

	In one step, you can move one cell up, down, left, or right. 
	You cannot step into a cell with a wall, and you cannot step outside the maze. 
	
	Your goal is to find the nearest exit from the entrance. An exit is defined as an empty cell that is at the border of the maze. 
	
	The entrance does not count as an exit.

	Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if no such path exists.
	*/

	

	vector<vector<char>> maze( 4,vector<char>(20, '+') );

	maze[1][16]='.';
	maze[1][17]='.';
	maze[1][18]='.';

	maze[2][16]='.';
	maze[2][17]='.';
	maze[2][18]='.';
	maze[2][19]='.';
	
	maze[3][17]='.';
	maze[3][18]='.';
	maze[3][19]='.';

 
	vector<int> entrance;


	
	entrance.push_back(2);
	entrance.push_back(16);

	int minPath = INT_MAX ;
	unordered_map<int,bool> visited; 

	// minPath will be our solution its passed by reference to be able to check different solutions
	// visited is a hashtable to save all visited nodes by making for ex if [1 0] -> so map[10] = 1; visited


	cout << Solve(maze,entrance,visited,0,minPath) << endl;

	

	//delete [] adjacencyList; 

	system("pause") ;
}