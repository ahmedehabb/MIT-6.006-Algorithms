#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
using namespace std; 




void addEdge(vector<pair<int, int> > adj[], int u, int v, int weight)
{
	
	adj[u].push_back(make_pair(v,weight));

	// i will be commenting this since we assume we work with directed graph 
    //	adj[v].push_back(make_pair(u,weight));
}

void RelaxEdge(vector<pair<int, int> > adj[] , int u , int v, int weight,
			   unordered_map<int,int>& predecessor,vector<int>& distance ){

	if(distance[v]> distance[u] + weight){
		distance[v] = distance[u] + weight;
		predecessor[v] = u ;
	}

}


vector<int> BellmanFord(vector<pair<int, int> > adj[], int start, int Vertices,unordered_map<int,int> &predecessor){


	vector<int> distance(Vertices,INT_MAX); // this is what we will return which is shortest distance from starting point for each vertex
	//all are initialized as int_max except start -> 0 in next line
	
	// initialzing start vertex
	distance[start] = 0 ;
	predecessor[start] = -1 ;
	

	// computation part
	for (int i = 0; i < Vertices; i++)
	{
		// we need to loop over all edges and relax them
		for (int j = 0; j < Vertices; j++)
		{

			for (int edge = 0; edge < adj[j].size(); edge++)
			{
				RelaxEdge(adj,j,adj[j][edge].first , adj[j][edge].second,predecessor,distance);
			}
		}
	}



	// checking part (-ve cycles) ;
	// we need to loop over all edges and check if we can relax any of them
	for (int j = 0; j < Vertices; j++)
	{
			for (int edge = 0; edge < adj[j].size(); edge++)
			{
				cout << "edge :"<< j  << " -> " << adj[j][edge].first << endl;
				cout << distance[adj[j][edge].first] << "  " <<  distance[j] + adj[j][edge].second << endl; 
				if(distance[adj[j][edge].first]> distance[j] + adj[j][edge].second){
					cout << " Negative cycle detected !!! " << endl ;
					
					// we will just clear
					predecessor.clear();
					distance.clear();
					return distance ;
				}
			}
	}	
	return distance ;
}



int main(){



	const int vertices = 5;
	vector<pair<int, int> > adj[vertices];
	
	/*
	// using these edges will produce same answer as before 

	addEdge(adj,0,1,10);
	addEdge(adj,0,2,3);

	addEdge(adj,1,2,1);
	addEdge(adj,2,1,4);

	addEdge(adj,1,3,2);
	addEdge(adj,2,3,8);
	addEdge(adj,2,4,2);

	addEdge(adj,3,4,9);
	addEdge(adj,4,3,7);
	*/

	// negative cycle example
	addEdge(adj,0,1,10);
	addEdge(adj,0,2,3);

	addEdge(adj,1,2,1);
	addEdge(adj,2,1,4);

	addEdge(adj,1,3,2);
	addEdge(adj,2,3,8);
	addEdge(adj,2,4,2);

	// by using -9 instead of 9 
	// here is the negative cycle edge(3,4)=-9 and edge(4,3)=7 so negative cycle and will be detected
	addEdge(adj,3,4,-9);
	addEdge(adj,4,3,7);

	unordered_map<int,int> predecessor;
	
	// source is 0 
	vector<int> distance = BellmanFord(adj, 0,vertices,predecessor);

	if(distance.size()){
		
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
	}

	

	system("pause");
}