#include<iostream>
#include<unordered_map>
#include <vector>
#include <string>
using namespace std; 


vector<vector<int>>  handleNeighbours(vector<vector<char>>& maze, vector<int>& entrance,vector<vector<int>>& visited,bool &border){

	// this bool border will change it to 1 -> mean we found a border element and you should finish
	// no need to continue finding other neighbours

	vector< vector<int> > adjacencyList ; // we will save [row,col] as an element 
	vector<int> x;	

	if( entrance[0]>0 && 
		(visited[entrance[0]-1][entrance[1]]==0) && // inorder not to get back
		 maze[entrance[0]-1][entrance[1]]=='.'){ // mean it can have upper child

		x.push_back(entrance[0]-1);
		x.push_back(entrance[1]);
		adjacencyList.push_back(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	if( entrance[0]< maze.size()-1 &&
		(visited[entrance[0]+1][entrance[1]]==0) && // inorder not to get back
		 maze[entrance[0]+1][entrance[1]]=='.'){ // mean it can have lower child
		x.push_back(entrance[0]+1);
		x.push_back(entrance[1]);
		adjacencyList.push_back(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}
	
	if( entrance[1]>0 &&
		(visited[entrance[0]][entrance[1]-1]==0) && // inorder not to get back
		 maze[entrance[0]][entrance[1]-1]=='.'){ // mean it can have left child
		x.push_back(entrance[0]);
		x.push_back(entrance[1]-1);
		adjacencyList.push_back(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	if( entrance[1]<maze[0].size()-1 &&
		(visited[entrance[0]][entrance[1]+1]==0) && // inorder not to get back
		 maze[entrance[0]][entrance[1]+1]=='.'){ // mean it can have right child
		x.push_back(entrance[0]);
		x.push_back(entrance[1]+1);
		adjacencyList.push_back(x);
		if( x[0]==0 || x[0]==maze.size()-1 || x[1]==0 || x[1]==maze[0].size()-1  ){
			border=1;
			return adjacencyList; // no need to continue
		}
		x.clear();
	}

	return adjacencyList;

}


	
int Solve(vector<vector<char>>& maze, vector<int> entrance,	vector<vector<int>>& visited,int level ,int &minpath) {

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
		[[".",".",".",".",".","+",".",".","."]
		,[".","+",".",".",".",".",".",".","."]
		,[".",".","+",".","+",".","+",".","+"]
		,[".",".",".",".","+",".",".",".","."]
		,[".",".",".",".","+","+",".",".","."]
		,["+",".",".",".",".",".",".",".","."]
		,[".",".",".","+",".",".",".",".","."]
		,[".",".",".","+",".",".",".",".","+"]
		,["+",".",".","+",".","+","+",".","."]]
		
		*/
	
	// Very tricky and important :: 
		// this is to ensure not to check a path which is longer than you minimum just backtrack 
	if(level+1 > minpath)
		return minpath;
	
	// if its entrance will be [1 0] -> so will take number 10 in hash table
	visited[entrance[0]][entrance[1]]=1 ;

	// border rows/ cols
	if(level!=0 && ( entrance[0]==0 || entrance[0]==maze.size()-1 || entrance[1]==0 || entrance[1]==maze[0].size()-1 ) ){
		visited[entrance[0]][entrance[1]]=0 ;
		return level;
	}
	bool border =0 ;

	

	vector<vector<int>> adjacency =	handleNeighbours(maze,entrance,visited,border);


	if(border && level+1 <minpath ){
		
		// unchecking the visited element in maze 
		// as it could be used in getting another path that could be better
		// without uncheking it at end --> you say that you will use it only once
		visited[entrance[0]][entrance[1]]=0;

		minpath= level+1;
		return minpath;
	}

	for(int i=0;i<adjacency.size(); i++){
		vector<int> temp = adjacency[i];
		//entrance = temp->getKey() ; 

		// will pass last visited as my current entrance
		// and new entrance will be temp->getkey as it is the neighbour 
		Solve(maze,temp,visited,level+1,minpath );
		

	}
	
	

	// There are tricky part here which is -->
		// unchecking the visited element in maze 
		// as it could be used in getting another path that could be better
		// without uncheking it at end --> you say that you will use it only once
	visited[entrance[0]][entrance[1]]=0 ;


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

	

	vector<vector<char>> maze( 9,vector<char>(9, '.') );

	//[".",".",".",".",".","+",".",".","."],
	//[".","+",".",".",".",".",".",".","."],
	//[".",".","+",".","+",".","+",".","+"],
	//[".",".",".",".","+",".",".",".","."],
	//[".",".",".",".","+","+",".",".","."],
	//["+",".",".",".",".",".",".",".","."],
	//[".",".",".","+",".",".",".",".","."],
	//[".",".",".","+",".",".",".",".","+"],
	//["+",".",".","+",".","+","+",".","."]

	maze[0][5]='+';
	maze[1][1]='+';
	maze[2][2]='+';
	maze[2][4]='+';
	maze[2][6]='+';
	maze[2][8]='+';
	maze[3][4]='+';
	maze[4][4]='+';
	maze[4][5]='+';
	maze[5][0]='+';
	maze[6][3]='+';
	maze[7][3]='+';
	maze[7][8]='+';
	maze[8][0]='+';
	maze[8][3]='+';
	maze[8][5]='+';
	maze[8][6]='+';

	vector<int> entrance;


	
	entrance.push_back(8);
	entrance.push_back(4);

	int minPath = INT_MAX ;


	// minPath will be our solution its passed by reference to be able to check different solutions
	// visited is a hashtable to save all visited nodes by making for ex if [1 0] -> so map[10] = 1; visited

	vector<vector<int>> visited( maze.size(),vector<int>(maze[0].size(), 0) );

	cout << Solve(maze,entrance,visited,0,minPath) << endl;

	

	//delete [] adjacencyList; 

	system("pause") ;
}