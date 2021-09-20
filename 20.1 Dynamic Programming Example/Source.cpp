#include<iostream>
using namespace std; 
#include<vector>
#include <algorithm>

int minCostStairs(vector<int>& cost){
		 
		// first represent first best possible for index i+1
        // second represent first best possible for index i+2

        int first = 0;
        int second = 0;
        int sol = 0 ;
        for(int i = cost.size()-1; i>=0 ; i-- ){
            sol = cost[i] + min (first,second);
            second = first;
            first = sol ; 
        }
        
		return min(sol,second); // since we could start from 0 or 1 
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

int countVowelStrings(int n) {
        // if you have seen matrix of sizes where
        //a   1    5    15  35
        //e   1    4    10  20
        //i   1    3    6   10
        //o   1    2    3    4
        //u   1    1    1    1    
             //1  //2  //3  //4  
        
        //where for u for any sizes we will just have 
        // size=1 ->u  (1)
        // size=2 ->uu (1)
        // size=3 ->uuu (1)
        // and so on 
        
        // while when turning to o
        // at size(1) you have o only (1)
        // at size(2) you are obliged to start with o so you have 1 remaining place empty
                // this place can be either o,u so 2 choices 
						// for easier , let matrix[o] represent the row of vowel"o" and same for others
                // this two choices = matrix[o][1] + matrix[u][1]
        // at size(3) you are obliged to start with o so you have 2 remaining place empty
                // this place can be either oo,ou,uu so 3 choices 
                // these 3 choices are matrix[o][2](oo,ou) + matrix[u][2] (uu)
        
        // while when turning to i
        // at size(1) you have i only (1)
        // at size(2) you are obliged to start with i so you have 1 remaining place empty
                // this place can be either i,o,u so 3 choices 
						// for easier , let matrix[i] represent the row of vowel"i" and same for others
                // this three choices = matrix[i][1]+ matrix[o][1] + matrix[u][1]
        // at size(3) you are obliged to start with i so you have 2 remaining place empty
                // this place can be either (ii,io,iu) , (oo,ou) , (uu) so 6 choices 
                // this three choices = matrix[i][2]+ matrix[o][2] + matrix[u][2]
        
        // and so on .... 
        
        // so its pretty appearing that 
            // for matrix[i][j] it depends on all matrix[k][j-1] where k>=i
        
        //but doing it by a loop will works but will be not a good way to do it..
        
        // so we gonna use the idea of (CUMULATION)
            // so wherever i go up i took the previous um i just calculated and go up with it
            // so for ex when calculating matrix[i][3]
                // matrix[i][3] = matrix[i][2]+ matrix[o][2] + matrix[u][2];
        
            //in order to do that
                // matrix[o][2] will not only be (oo,ou) but it will also carry (uu) with it
                // so we wont need to loop over them again
                
                // so same for matrix[i][2] it will be (ii,io,iu,  oo,ou , uu)
        
            // so our Calculation now changes to be
                    // matrix[i][3]= matrix[i][2] + matrix[o][3] only;
            
            // and matrix[o][3] also carry o and u elements (ooo,oou,ouu   ,uuu)
            //(thats it)!!
                
        // so for size(i) all possible solutions will be accumulated and summed up to be                //found at first row at the end
            
        int **matrix = new int*[5];

        for(int i=0;i<5;i++){
			matrix[i] = new int[n+1];
            matrix[i][0]=1;
        }
        for(int i=0;i<n+1;i++){
            matrix[4][i]=1 ;
        }
        
        for(int i=1;i<=n;i++){
            for(int j=3; j>=0;j--){
               matrix[j][i]=matrix[j+1][i] + matrix[j][i-1];
            }
        }
        

        int result = matrix[0][n];

		for(int i=0;i<5;i++){
			delete [] matrix[i] ;
        }
		delete [] matrix ;
		return result ;
    }

int main(){

	//// 1.problem definition
		///////////////////////////////////

	//problem min cost climbing stairs
	//	You are given an integer array cost where cost[i] is the cost of ith step on a staircase.Once you pay the cost, you can either climb one or two steps.
	//You can either start from the step with index 0, or the step with index 1.
	//Return the minimum cost to reach the top of the floor.

	/*
	int arr[] = {1,100,1,1,1,100,1,1,100,1};

	vector<int> cost;
	for(int i=0; i<10; i++)
		cost.push_back(arr[i]) ;

	cout<< minCostStairs(cost)<<endl;
	*/

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

	//cout << divisorGame(100)<<endl;

	///////////////////////////////////

	//problem min cost climbing stairs
	/*int arr[] = {1,100,1,1,1,100,1,1,100,1};

	vector<int> cost;
	for(int i=0; i<10; i++)
		cost.push_back(arr[i]) ;

	cout<< minCostStairs(cost)<<endl;*/




	//////////////////////////

	// problem 1641. Count Sorted Vowel Strings

	//	Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
	//
	//A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.

	cout << countVowelStrings(10)<<endl ;


	system("pause");
}