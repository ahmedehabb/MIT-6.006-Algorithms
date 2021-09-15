#include<iostream>
#include<unordered_map>
#include <vector>
#include <string>
using namespace std; 



vector<vector<int>> handleNeighbours2(vector<vector<char>>& maze, vector<int>& entrance){

	int row=entrance[0],col=entrance[1];
	vector<vector<int>> newbies ;
	if( entrance[0]>0 &&
		 maze[row-1][col]=='.'){ // mean it can have upper child


		maze[row-1][col]='+';
        vector<int> x ;
		x.push_back(row-1);
		x.push_back(col);
		newbies.push_back(x);
	}

	if( row< maze.size()-1 &&
		 maze[row+1][col]=='.'){ // mean it can have lower child

		maze[row+1][col]='+';

        vector<int> x ;
		x.push_back(row+1);
		x.push_back(col);
		newbies.push_back(x);
	}
	
	if( col>0 &&
		 maze[row][col-1]=='.'){ // mean it can have left child

		maze[row][col-1]='+';

        vector<int> x ;
		x.push_back(row);
		x.push_back(col-1);
		newbies.push_back(x);
	
	}

	if( col<maze[0].size()-1 &&
		 maze[row][col+1]=='.'){ // mean it can have right child
        
		maze[row][col+1]='+';
        vector<int> x ;
		x.push_back(row);
		x.push_back(col+1);
		newbies.push_back(x);
	}
	return newbies ;

}


int Solve2(vector<vector<char>>& maze, vector<int> entrance){
		
		// this is important as we could return back to it 
        maze[entrance[0]][entrance[1]]='+';

        int minpath = INT_MAX ;
		vector<vector<int>> frontier,adj;
		frontier.push_back(entrance);

		int currentlevel = 1; 
	
        int rows = maze.size(), cols= maze[0].size();

    
		while (frontier.size())
		{
			vector<vector<int>> next;

			for (int i = 0; i < frontier.size(); i++)
			{

				// this function get all possible neighbours and marks them + so we dont reach them again 
				// we could leave them as they are and check inside next for loop but must make flag or whatever
				adj= handleNeighbours2(maze,frontier[i]);

				for (int j = 0; j < adj.size(); j++)
				{
						next.push_back(adj[j]);
						// check border ?
						if( adj[j][0]==0 || adj[j][0]==rows-1 || adj[j][1]==0 || adj[j][1]==cols-1  ){
							if(currentlevel<minpath){
                                minpath=currentlevel;
                            }
						}
				}
			
			}
			frontier = next ;
			currentlevel +=1; 
		}

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

	

	vector<vector<char>> maze( 4,vector<char>(5, '+') );

	maze[0][3]='.';

	maze[1][1]='.';
	maze[1][2]='.';
	maze[1][3]='.';

	maze[2][0]='.';
	maze[2][1]='.';
	maze[2][2]='.';
	maze[2][3]='.';

	maze[3][3]='.';
	maze[3][4]='.';

	vector<int> entrance;


	
	entrance.push_back(1);
	entrance.push_back(2);

	

		int minPath = INT_MAX ;
        
        

	    minPath =Solve2(maze,entrance);

	
        if(minPath==INT_MAX)
	        minPath =-1 ;

		cout << minPath << endl ;

	system("pause") ;
}