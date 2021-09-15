#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std; 

void minHeapify(vector<pair<int,int> > &A, int index, int size){
	if (index<0)
		return;


	int left = 2* index +1 ;
	int right = 2* index + 2;
 
	if(left >= size && right>=size) // this means its leaf node and doesnt have any child
		return ; 

	// we made a very important assumption that left and right subtrees must be max heaps 
	// so we could only have 1 incorrect position and need to fix it not more than 1 
	

	// checking if only one child exists
	if(left < size && right >= size){
		if(A[index].second > A[left].second){
			pair<int,int> temp  = A[index] ; 
			A[index]= A[left];
			A[left]= temp ; 
			minHeapify(A,left,size) ;
		}
	}
	else if(right < size && left >= size){
		if(A[index].second > A[right].second){ // so right should be root 
			pair<int,int> temp  = A[index]; 
			A[index] = A[right] ;
			A[right] = temp ; 
			minHeapify(A,right,size) ;
		}
	}
	else // if both left and right children exists
	{
		// first we must get max of them as we will swap with maximum one 
		if(A[left].second<A[right].second && A[index].second > A[left].second) // if left> right so take it but must also be > root
		{
			// we must check that A[index] smaller than left to change them
				pair<int,int> temp  = A[index]; 
				A[index]= A[left];
				A[left]= temp ; 
				minHeapify(A,left,size) ;
			
		}else if (A[right].second < A[left].second && A[index].second > A[right].second)
		{
			
				pair<int,int> temp  = A[index] ; 
				A[index]= A[right];
				A[right] = temp ; 
				minHeapify(A,right,size) ;
		}
	}
}

void buildHeap(vector<pair<int,int>>A, int size){
	
	// here we start from size/2 since from [ size/2 + 1 .... end] these all are leaves 
	// and leaves are max heaps by definition
	for(int i=size/2 ; i>=0 ; i--){
		minHeapify(A,i,size) ;
	}
}


pair<int,int> extractMin(vector<pair<int,int>>&A){


		int size= A.size();

		pair<int,int> min = A[0] ;  // since its min heap 
		// swapping min element with last element in array 
		A[0] = A[size-1] ; 
		A[size-1 ] = min ; 
		
		A.pop_back();
		// this remove last element and dec size by 1

		// generally now our heap is not max heap since root isnt max 
		minHeapify(A,0,A.size() ) ;
	
		return min ;
}

void decreaseNode(vector<pair<int,int>>&A, int oldValue , int newValue, int first= 0 ){
	if(first>=A.size())
		return ;

	if(oldValue == A[first].second)
	{
		// root
		A[first].second = newValue ;
		int temp = (first -1) / 2;
		while(temp>=0){
			minHeapify(A,temp,A.size()) ;
			if(temp==0) 
				return;
		}
		// heaping up
	}else
	{
		int left = 2* first +1 ;
		int right = 2* first + 2;
		if (left>=A.size())
		{
			return ;
		}

		if(oldValue>=A[left].second && oldValue>=A[right].second){
			decreaseNode(A,oldValue,newValue,left) ;
			decreaseNode(A,oldValue,newValue,right) ;
		}
		else if(oldValue>=A[left].second){
			decreaseNode(A,oldValue,newValue,left) ;
		}else
			decreaseNode(A,oldValue,newValue,right) ;
	
	}
	

}


void addEdge(vector<pair<int, int> > adj[], int u, int v, int weight)
{
	
	adj[u].push_back(make_pair(v,weight));

	// i will be commenting this since we assume we work with directed graph 
    //	adj[v].push_back(make_pair(u,weight));
}

void RelaxEdge(vector<pair<int, int> > adj[] , int u , int v, int weight,
			   unordered_map<int,int>& predecessor,vector<int>& distance,vector<pair<int,int>> & Q ){



	if(distance[v]> distance[u] + weight){

		decreaseNode(Q,distance[v],distance[u] + weight);
		distance[v] = distance[u] + weight;
		predecessor[v] = u ;
	}

}

vector<int> Dijkstra(vector<pair<int, int> > adj[], int start, int Vertices,unordered_map<int,int> &predecessor){
	

	vector<int> distance(Vertices); // this is what we will return which is shortest distance from starting point for each vertex
	//all are initialized as int_max except start -> 0 in next line

	vector< pair<int,int> > Q ; 
	//Q : Priority Queue containing where Q[any] = {i,d} ; mean distance from source to vertex of index i = d; 
	
	for (int i = 0; i < Vertices; i++)
	{
		distance[i]= INT_MAX - Vertices -1+ i ;
		Q.push_back(make_pair(i,INT_MAX- Vertices -1+i));
	}
	
	predecessor[start] = -1 ;
	// here we changed initialized Q[start] = (with index =start , distance = 0) ; 
	distance[start] = 0 ;
	Q[start] = make_pair(start,0);

	buildHeap(Q,Q.size());
	
	while (Q.size())
	{
		pair<int,int> u = extractMin(Q);
		// for looping over adj vertices to u ->  adj[u.first].size() -> mean adj[ index of u ].size() 
		for (int i = 0; i < adj[u.first].size(); i++)
		{
			RelaxEdge(adj,u.first,adj[u.first][i].first,adj[u.first][i].second,predecessor,distance, Q);
		}
	}
	

	return distance ;
}





int main(){

	
	// Representation of graph 
		/*
		vector : A sequence container. Here we use it to store adjacency lists of all vertices. We use vertex number as index in this vector.
		pair : A simple container to store pair of elements. 
		
		Here we use it to store adjacent vertex number and weight of edge connecting to the adjacent.
			->The idea is to use a vector of pair vectors. 
				so for ex 	adj[1].push_back(make_pair(2,10)); mean there is edge from 1 to 2 and wight =10 ;
		*/
	// here i'm using min heaps -> theta(vlgv + Elgv)
	// and for more better -> we must use fib heap ( will do it later)  -> theta(vlgv + E)


	// doing example in lecture

	const int vertices = 5;
	vector<pair<int, int> > adj[vertices];

	addEdge(adj,0,1,10);
	addEdge(adj,0,2,3);

	addEdge(adj,1,2,1);
	addEdge(adj,2,1,4);

	addEdge(adj,1,3,2);
	addEdge(adj,2,3,8);
	addEdge(adj,2,4,2);

	addEdge(adj,3,4,9);
	addEdge(adj,4,3,7);

	unordered_map<int,int> predecessor;
	
	// source is 0 
	vector<int> distance = Dijkstra(adj,0,vertices,predecessor);


	cout << "printing distance from source for all vertices " << endl ;
		
	for (int i = 0; i < distance.size(); i++)
	{
		cout << distance[i] << endl ;
	}



	///////////////////////////////////////

	cout << "printing paths for all vertices " << endl ;

	for (int i = 0; i < vertices; i++)
	{
		cout << "for vertex " << i << endl ;
		int mypredecessor = predecessor[i]; 
		while (mypredecessor!=-1)
		{
			cout << mypredecessor << " " ;
			mypredecessor = predecessor[mypredecessor];
		}
		cout << endl ;
	}

	system("pause");
}