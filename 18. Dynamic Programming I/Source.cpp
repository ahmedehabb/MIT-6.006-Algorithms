#include<iostream>
#include<unordered_map>
using namespace std; 

int fib(int n){ 
	
	// here we assuming fib(n) is 1 indexed not 0 indexed
	//fib(1) = 1;
	//fib(2) = 1;


	if (n<=2)
	{
		return 1 ;
	}

	// in reality we dont need to keep track of all previously made computations
	// we just need last 2 computed as fib(n) = fib(n-1) + fib(n-2) ;
	
	// so think of this algorithm as incremental development of calculation of fib(n)

	// to get fib(n) we need fib(n-1) , fib(n-2)
	// so its like an array [1 1 2 3 5 8 .. ] and you are filling all the array n slots using last 2 computed 
	
	
	int first =1 ;
	int last = 1;
	int fib = 0 ;
	// will begin from 3rd one 
	for (int i = 3; i <= n; i++)
	{
		fib = first + last ;
		//updating values
		first = last;
		last =fib;

	}
	return fib ;
}


void addEdgeBidirectionally(vector<pair<int, int> > adjF[],vector<pair<int, int> > adjB[], int u, int v, int weight)
{
	
	adjF[u].push_back(make_pair(v,weight));
	adjB[v].push_back(make_pair(u,weight));

}


		
int shortestPath_Acyclic(vector<pair<int, int> > adj[],vector<pair<int, int> > backwardEdges[] , 
				 int start,int target, int Vertices,unordered_map<int,int>& memo){
	
	if(start==target){
		return 0 ;
	}

	if (memo.find(target) != memo.end())
	{
		// actually found
		return memo[target]; 
	}

	//else we need to compute it 
	int min = INT_MAX ;
	int temp = 0 ;
	//this for loop gets all edges where (u, target) for all possible u
	for (int i = 0; i < backwardEdges[target].size(); i++)
	{
		int u =  backwardEdges[target][i].first;
		// weight of (u,v) will be backwardEdges[target][i].second;
		temp = shortestPath_Acyclic(adj,backwardEdges,start, u ,Vertices,memo) + backwardEdges[target][i].second ;
		if(min > temp)
			min = temp ;
	}
	
	// now we need to save that in memo
	memo[target] = min ;
	return memo[target];

}




int main() {

	/*
	cout << "fib numbers " << endl ;
	// calculating first 20 fib numbers
	for (int i = 1; i < 21; i++)
	{
		cout << fib(i) << endl;
	}
	*/

	/////////////////////////////////

	const int vertices = 5;
	vector<pair<int, int> > adj[vertices];
	
	vector<pair<int, int> > backwardEdges[vertices]; 
	// we could actually dont have that but it helps as instead for searching whole edges in adj 
	// for(u,v) where v is our target we could just have them from backwardEdges[v] for faster 


	addEdgeBidirectionally(adj,backwardEdges,0,1,10);
	addEdgeBidirectionally(adj,backwardEdges,0,2,3);

	
	// must remove it bec it will cause a cycle
	//addEdgeBidirectionally(adj,backwardEdges,1,2,1);
	
	addEdgeBidirectionally(adj,backwardEdges,2,1,4);

	addEdgeBidirectionally(adj,backwardEdges,1,3,2);
	addEdgeBidirectionally(adj,backwardEdges,2,3,8);
	addEdgeBidirectionally(adj,backwardEdges,2,4,2);

	// must remove it bec it will cause a cycle
	//addEdgeBidirectionally(adj,backwardEdges,3,4,9);

	addEdgeBidirectionally(adj,backwardEdges,4,3,7);

	unordered_map<int,int> predecessor;
	
	unordered_map<int,int> memo; 
	int start = 0 ;

	// in this memo we will save delta(s,v)
	// since our source is the same so we dont need to save it here 
	// memo[v] = (delta from s to v) "min weight" 

	// so to go from start to start -> 0 weighted path
	memo[start] = 0 ; 


	cout << "using the single target method" << endl ;
	for (int i = 0; i < vertices; i++)
	{
		// proof that single source single target works 
		// here we are repeating the problem multiple times for each target not continuing 
		int distance = shortestPath_Acyclic(adj,backwardEdges,0,i,vertices,memo);
		cout << "from source " << 0 << " to target " << i << " : " << distance << endl ;
	}

	//////////////////////////////////////////////
	// WHAT IF ITS CYCLIC !!!!!!!
	
	//in order to solve cyclic graphs
		// you will need to put another aspect in your search which will prevent you from infinite recursion
		// this aspect is distance where we just stop when distance = 0 ;

	// our goal is convert cyclic graphs into acyclic prespective

	//for ex if we have cyclic graph( vertices : S A B C ) 
		// so we will make V-1 LAYERS (EACH LAYER CONTAINS ALL VERTICES EXCEPT LAYER 0 CONTAINS JUST SOURCE)
		
		// so layer 0 -> we have only S0
		// so layer 1 -> we have only S1,A1,B1,C1
		// so layer 2 -> we have only S2,A2,B2,C2
		// so layer 3 -> we have only S3,A3,B3,C3

		// and between each layer there is our regular edges 
		// so if we have (S,A) in real graph 
			// So there'll be (S0,A1) , (S1,A2) , (S2,A3)

		// so our longest path in size will be (V - 1) AS GOING THROGH ALL LAYERS

	// What this algorithm claims that if you want to go from s to v for ex
		// so you can go V-1 times depending on distance you have
		// and get shortest path from s to v for all distances possible

		// SO THATS SO HELPFUL IF YOU TAKE DISTANCE IN CONSIDERATION WITH SHORTEST PATH ALSO LIKE (GAS STATION FOR EX)
		
	// so our structure will be like 
		//		S1	S2	S3
		//		A1	A2	A3
		// SO	B1	B2	B3
		//		C1	C2	C3 

	// IN TERMS OF COMPLEXITY = O(VERTICES + EDGES) USING DAG ALGORITHM
			//WE HAVE VERTICES = V(V-1)+1 = O(V^2)
			//WE HAVE EDGES = (V-2)E + outdegree(S0) = O(VE + E(max outdegree) ) = O(VE)
	// SO TOTAL COMPLEXITY = O(V^2 + VE) = O(V^3) since E=O(V^2)
		//this complexity is same to bellman-ford's one 

	// Actually THIS IS BELLMAN FORD ALGORITHM BUT FROM DP PRESPECTIVE think of it!!!!!!!!!!!!
	// go see it in topic 16
	
	
	
	system("pause") ;
}