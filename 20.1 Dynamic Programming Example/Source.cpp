#include<iostream>
using namespace std; 
#include<vector>
#include <algorithm>

int maxSatisfaction(vector<int>& satisfaction) {
	
	int size =satisfaction.size() ;

	sort(satisfaction.begin(),satisfaction.end());

	int** matrix = new int*[size+2] ;

	for (int i = 0; i < size+2; i++)
	{
		matrix[i] = new int[size+2];
	}
	for (int i = 0; i < size+2; i++)
	{
		matrix[size+1][i]= 0 ;
		matrix[i][size+1]= 0 ;
		matrix[i][0] = 0;
		matrix[0][i] = 0;
	}
	
	
	

		for (int i = size; i >=1; i--)
		{
			for (int j = 1; j <=size; j++)
			{
				matrix[i][j] = max(matrix[i+1][j] , matrix[i+1][j+1]+satisfaction[i-1]*j) ;
			}
		}
	

	

		int solution =matrix[1][1];
		// deallocation
		for (int i = 0; i < size+1; i++)
		{
			delete [] matrix[i];
		}
		delete [] matrix;


		return solution;
}


vector<int> countBits(int n) {
	vector<int>  DP(n+1);
	DP[0]=0;

	// just initializing

	int nextTwoPower = 1;
	// twoPowers are 1,2,4,8,16,32,... 
	
	//as we will detect if they exist so --> counter = 1;

	int counter= 1;

	for (int i = 1; i < n+1;)
	{    

		// since i enters = 1 (two powers)
		//since each TwoPower last in iteration (twoPower-1 ) iterations then it changes
		// ex : 8 (1000) last 7 iterations and all like that

		// (101) we used to look it as 4(100) + 1(001) 
			// as we know 4 -> two Powers

		DP[i] =1;

		// you could think thats is nested loops (so O(|i|.|j|) but its wrong as i doesnt iterate 1 by one 
		// we iterate i and j together linearly = n
		for (int j = 1; j <= nextTwoPower-1 && i+j<n+1; j++)
		{
			DP[i+j] = DP[i] + DP[j];
		}
		
		nextTwoPower *=2 ;
		i = nextTwoPower ;
		
	}
	return DP;
}

vector<int> countBits2(int n) {
	vector<int>  DP(n+1);
	DP[0]=0;

	//this solution is easier as looking at binary number from the different way
	// prev example (101) we used to look it as 4(100) + 1(001) 

	// but this example (101) --> left (10)+ right(1) as last bit = i%
	// its easier way but same Time!!!

    for (int i = 1; i < n+1;i++)
	{    
		DP[i]= DP[i/2] + i%2 ;
	}
    
	return DP;
}


bool divisorGame(int n) {
        int *WinTable= new int[n+1];
        // ignore 0 index to be easy
        
		if(n<=2)
            return n-1;

        
        WinTable[1] = 0 ; // 0 mean fail
        WinTable[2] = 1 ; // mean success;
        
        
        for(int i=3;i<n+1;i++)
        {
			WinTable[i]=false;
			
			for(int j=1;j<=sqrt(i);j++){
				//j<=sqrt(i); is enough as we cant find i%j==0 for j>sqrt(i) 
				// Composite Number has Prime Factor not Greater Than its Square Root
				// https://proofwiki.org/wiki/Composite_Number_has_Prime_Factor_not_Greater_Than_its_Square_Root

                if(i%j==0 && WinTable[i-j]==0){
                    WinTable[i]=true;
                    break ;
                }
            }
            
        }
        return WinTable[n];
}

int main(){

	//// 1.problem definition
	///*
	//A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

	//Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level  
	//i.e.  time[i]*satisfaction[i]

	//Return the maximum sum of Like-time coefficient that the chef can obtain after dishes preparation.

	//Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value
	//*/
	//vector<int> satisfaction;
	//int satisfactionCopy[] = {2,3,4};
	//
	//
	//for (int i = 0; i < 3; i++)
	//{
	//	satisfaction.push_back(satisfactionCopy[i]);
	//}
	////cout << maxSatisfaction(satisfaction)<<endl;
	//sort(satisfaction.begin(),satisfaction.end());
	////////////////////////////////////////////////////////////////////////////



	//2. Counting bits (338. Counting Bits LeetCode)
	//Given an integer n, return an array ans of length n + 1 
	//such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.
	
	//int n = 2;
	//vector<int> sol =countBits(n);
	////vector<int> sol =countBits2(n); // you could try if you need

	//for (int i = 0; i < sol.size(); i++)
	//{
	//	cout << sol[i] << " " ;
	//}
	//cout << endl ;

	/////////////////////////////////////////////////////////////////////////////
	
	// 3. Divisor Game

	//	Alice and Bob take turns playing a game, with Alice starting first.
	//
	//Initially, there is a number n on the chalkboard. On each player's turn, that player makes a move consisting of:
	//
	//Choosing any x with 0 < x < n and n % x == 0.
	//Replacing the number n on the chalkboard with n - x.
	//Also, if a player cannot make a move, they lose the game.
	//
	//Return true if and only if Alice wins the game, assuming both players play optimally.

	cout << divisorGame(100)<<endl;


	system("pause");
}