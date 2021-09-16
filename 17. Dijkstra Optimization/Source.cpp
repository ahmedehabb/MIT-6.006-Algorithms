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

void buildHeap(vector<pair<int,int>>&A, int size){
	
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

void decreaseNode(vector<pair<int,int>>&A,int index, int oldValue , int newValue, int first= 0 ){
	if(first>=A.size())
		return ;

	// check value and index also not only value as at first all have same value MAX_INT so cant compare values only
	if(index==A[first].first && oldValue == A[first].second)
	{
		// root
		A[first].second = newValue ;
		int temp = (first -1) / 2;
		while(temp>=0){
			minHeapify(A,temp,A.size()) ;
			temp = (temp -1) / 2;
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

		if(right<A.size() && oldValue>=A[left].second && oldValue>=A[right].second){
			decreaseNode(A,index,oldValue,newValue,left) ;
			decreaseNode(A,index,oldValue,newValue,right) ;
		}
		else if(oldValue>=A[left].second){
			decreaseNode(A,index,oldValue,newValue,left) ;
		}else
			decreaseNode(A,index,oldValue,newValue,right) ;
	
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

		decreaseNode(Q,v,distance[v],distance[u] + weight);
		distance[v] = distance[u] + weight;
		predecessor[v] = u ;
	}

}


// this is normal dijkstra where we have one source (All or any target)
vector<int> Dijkstra(vector<pair<int, int> > adj[], int start, int Vertices,unordered_map<int,int> &predecessor){
	

	vector<int> distance(Vertices); // this is what we will return which is shortest distance from starting point for each vertex
	//all are initialized as int_max except start -> 0 in next line

	vector< pair<int,int> > Q ; 
	//Q : Priority Queue containing where Q[any] = {i,d} ; mean distance from source to vertex of index i = d; 
	
	for (int i = 0; i < Vertices; i++)
	{
		distance[i]= INT_MAX;
		Q.push_back(make_pair(i,INT_MAX));
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


// this is single source , single target dijkstra
// the optimization we can do is to stop when we reach our target (no need to process whole graph (till emptying Q) )
vector<int> Dijkstra_SingleSource_SingleTarget(vector<pair<int, int> > adj[], int start,int target, 
											   int Vertices,unordered_map<int,int> &predecessor){
	

	vector<int> distance(Vertices); // this is what we will return which is shortest distance from starting point for each vertex
	//all are initialized as int_max except start -> 0 in next line

	vector< pair<int,int> > Q ; 
	//Q : Priority Queue containing where Q[any] = {i,d} ; mean distance from source to vertex of index i = d; 
	
	for (int i = 0; i < Vertices; i++)
	{
		distance[i]= INT_MAX;
		Q.push_back(make_pair(i,INT_MAX));
	}
	
	predecessor[start] = -1 ;
	// here we changed initialized Q[start] = (with index =start , distance = 0) ; 
	distance[start] = 0 ;
	Q[start] = make_pair(start,0);

	buildHeap(Q,Q.size());
	
	pair<int,int> u = extractMin(Q);
	
	while (u.first != target)
	{
		// for looping over adj vertices to u ->  adj[u.first].size() -> mean adj[ index of u ].size() 
		for (int i = 0; i < adj[u.first].size(); i++)
		{
			RelaxEdge(adj,u.first,adj[u.first][i].first,adj[u.first][i].second,predecessor,distance, Q);
		}
		u = extractMin(Q) ;
	}
	

	return distance ;
}



/////////////////////////////////////////////////
//Bidirectional dijkstra :

// Bidirectional dijkstra where we move forward from source and backward from target untill we meet 


void addEdgeBidirectionally(vector<pair<int, int> > adjF[],vector<pair<int, int> > adjB[], int u, int v, int weight)
{
	
	adjF[u].push_back(make_pair(v,weight));
	adjB[v].push_back(make_pair(u,weight));

}



int Bidirectional_Dijkstra(vector<pair<int, int> > adjF[],vector<pair<int, int> > adjB[], int start,int target ,int Vertices,
					 unordered_map<int,int> &predecessorForward,unordered_map<int,int> &predecessorBackward, int &Mediumvertex){
	
	// will return minPath

	vector<int> distanceF(Vertices); // distance forward
	vector<int> distanceB(Vertices); // distance backward


	//Q : Priority Queue containing where Q[any] = {i,d} ; mean distance from source to vertex of index i = d; 
	vector< pair<int,int> > Qf ; // Q forward
	vector< pair<int,int> > Qb ; // Q backward
	
	for (int i = 0; i < Vertices; i++)
	{
		distanceF[i]= INT_MAX;
		distanceB[i]= INT_MAX;
		Qf.push_back(make_pair(i,INT_MAX));
		Qb.push_back(make_pair(i,INT_MAX));
	}
	
	// TAKE CARE !! 
	// PredecessorForward is different from predecessor backward
		// if we have an edge (u,v) mean directed from u to v as follows U---->V
		// in forwardpredecessor , forwardpredecessor[V]=U
		// in backwardpredecessor , backwardpredecessor[U]=V as imagine inverse of direction of edge
	predecessorForward[start] = -1 ;
	predecessorBackward[target] = -1 ; 

	// here we changed initialized Q[start] = (with index =start , distance = 0) ; 
	distanceF[start] = 0 ;
	distanceB[target] = 0 ;

	Qf[start] = make_pair(start,0);
	Qb[target] = make_pair(target,0);

	buildHeap(Qf,Qf.size());
	buildHeap(Qb,Qb.size());
	
	pair<int,int> uF = extractMin(Qf);
	pair<int,int> uB = extractMin(Qb);

	if(uF.first==uB.first){
		Mediumvertex = uF.first ;
		return 0 ; 
	}
	
	while (uF.first!=uB.first && uF.first != target)
	{
		// for looping over adj vertices to u ->  adj[u.first].size() -> mean adj[ index of u ].size() 
		for (int i = 0; i < adjF[uF.first].size(); i++)
		{
			RelaxEdge(adjF,uF.first,adjF[uF.first][i].first,adjF[uF.first][i].second,predecessorForward,distanceF, Qf);
		}

		// for looping over adj vertices to u ->  adj[u.first].size() -> mean adj[ index of u ].size() 
		for (int i = 0; i < adjB[uB.first].size(); i++)
		{
			RelaxEdge(adjB,uB.first,adjB[uB.first][i].first,adjB[uB.first][i].second,predecessorBackward,distanceB, Qb);
		}

		uF = extractMin(Qf);
		uB = extractMin(Qb);
	}

	int minpath = distanceF[uF.first] + distanceB[uF.first];
	// but remember this could be not the shortest path as mentioned in an example in lecture so must check 
	
	Mediumvertex = uF.first ;// will keep track of it to get path itself

	for (int i = 0; i < Vertices; i++)
	{
		// inorder not to happen overflow we have not to check vertices which we didnt pass on and ther distances arent changed
		if (distanceF[i]!=INT_MAX && distanceB[i]!=INT_MAX && minpath > distanceF[i] + distanceB[i])
		{
			minpath = distanceF[i] + distanceB[i];
			Mediumvertex = i ;
		}
	}

	return minpath;

}

// get path of bidrectional dijkstra 
vector<int> path_Bidirectional_Dijkstra(int Mediumvertex, unordered_map<int,int> &predecessorForward,
										unordered_map<int,int> &predecessorBackward){
					 
		
	
	// first we will get backward from medium to source so to get that in order we must have a stack like ds 
	// so we push medium then level before it and so on till we reach source
	vector<int> path ; 

	path.push_back(Mediumvertex) ;
	
	int temp = Mediumvertex ;
	while (predecessorForward[temp]!=-1)
	{
		path.push_back(predecessorForward[temp]) ;
		temp = predecessorForward[temp] ;
	}

	// now path contain (medium .. levelbefore .. so on till Source) ;
	
	// so we need right order (Source .. level after .. so on till medium );
	// so we gonna push from end to 1st in another vector
	vector<int> correctPath ; 
	for (int i = path.size()-1; i >=0; i--)
	{
		correctPath.push_back(path[i]);
	}

	// so now we need to have from medium to level after it and so on till target
	// this is pretty easier as we have predecessor backward it will get us there easily (no need to revert as above) ;
	temp =Mediumvertex;
	while (predecessorBackward[temp]!=-1)
	{
		correctPath.push_back(predecessorBackward[temp]) ;
		temp = predecessorBackward[temp] ;
	}


	return correctPath;
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
	int source =0 , target =4 ;

	vector<int> distance = Dijkstra(adj,source,vertices,predecessor);

	cout << "using all/any target " << endl ;
	for (int i = 0; i < distance.size(); i++)
	{
		cout << "from source " << source << " to target " << target << " : " << distance[i] << endl ;
	}


	cout<< " ***********************" << endl;

	cout << "using the single target method" << endl ;
	for (int i = 0; i < vertices; i++)
	{
		// proof that single source single target works 
		// here we are repeating the problem multiple times for each target not continuing 
		vector<int> distance2 = Dijkstra_SingleSource_SingleTarget(adj,source,i,vertices,predecessor);
		cout << "from source " << source << " to target " << i << " : " << distance2[i] << endl ;
	}
	 

	///////////////////
	cout<< " ***********************" << endl;
	cout << "using Bidirectional Dijkstra" << endl ;


	// F: Forward;
	// B: Backward;

	vector<pair<int, int> > adjF[vertices]; // this is forward edges
	vector<pair<int, int> > adjB[vertices]; //  this is backward edges

	// here we will use addEdgeBidirectionally as it saves edges in both vertices
		//ex : (u,v) its directed from u to v
		// so adjF saves it in the same original direction
		// while adjB save it in backward direction as (v,u)
	addEdgeBidirectionally(adjF,adjB,0,1,10);
	addEdgeBidirectionally(adjF,adjB,0,2,3);

	addEdgeBidirectionally(adjF,adjB,1,2,1);
	addEdgeBidirectionally(adjF,adjB,2,1,4);

	addEdgeBidirectionally(adjF,adjB,1,3,2);
	addEdgeBidirectionally(adjF,adjB,2,3,8);
	addEdgeBidirectionally(adjF,adjB,2,4,2);

	addEdgeBidirectionally(adjF,adjB,3,4,9);
	addEdgeBidirectionally(adjF,adjB,4,3,7);

	unordered_map<int,int> predecessorF;
	unordered_map<int,int> predecessorB;
	int Mediumvertex = 0 ;

	for (int i = 0; i < vertices; i++)
	{
		// repeat for all targets
		cout <<"min path from source 0 to " << i << " =" << Bidirectional_Dijkstra( adjF,adjB, 0,i ,vertices,
			predecessorF,predecessorB,Mediumvertex) << endl ;
		
		cout << "path :" << endl ;
		vector<int> path = path_Bidirectional_Dijkstra(Mediumvertex,predecessorF,predecessorB);
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << " " ;
		}
		cout << endl ;
	}
	
	system("pause");
}