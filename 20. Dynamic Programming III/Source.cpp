#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

// Edit distance
int minDistance(string word1, string word2) {
        
		int n = word1.size();
        int m = word2.size();
        
		if(n==0){
            return m ;
        }else if(m==0){
            return n ;
        }

		// Allocation of matrix since C++ doesnt allow for arrays to be made with non const int
        int **matrix = new int*[n+1];
		for (int i = 0; i < n+1; i++)
		{
			matrix[i]= new int[m+1];
		}


		// since last col represent matrix[0..n][m]
			// this last column shows that size of suffix of y = 0
			// so when x[n][m] -> also size of x =0 so cost =0;
			// but as we go up size of x increases so cost increases by same as size of suffix of x since y is empty
        for(int i=n;i>=0;i--){
            matrix[i][m]= n-i ;
        }
		// same for last row 
        for(int i=m;i>=0;i--){
            matrix[n][i]= m-i ;
        }
        
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                if(word1[i]==word2[j]){
					// if same char -> so no more cost than prev made at i+1,j+1
                    matrix[i][j]= matrix[i+1][j+1];
                }else            
					// else we will do cost of 1 + min(any of 3 operations:insert,delete,replace);
                    matrix[i][j]=1+ min(matrix[i+1][j+1],
                                  min(matrix[i+1][j],matrix[i][j+1]) );
                 }
        }
        int result =matrix[0][0];

		// deallocation
		for (int i = 0; i < n+1; i++)
		{
			delete [] matrix[i];
		}
		delete [] matrix;


		return result;
}


// Knapsack problem !
int knapSack(int W,vector<int> sizes,vector<int> values , vector<bool>& taken){
	int n= sizes.size();
	vector<vector<int>> matrix(n+ 1, vector<int>(W + 1, 0));

	for (int i = n-1; i >=0; i--)
	{
		for (int j = 0; j <=W; j++)
		{
			if (j-sizes[i]>=0)
			{
				matrix[i][j] = max(matrix[i+1][j] ,matrix[i+1][j-sizes[i]] + values[i] ) ; 
				
			}else{
				matrix[i][j] = matrix[i+1][j];
			}
		}
	}
	
	// to get taken or not you must do reverse path
	int i =0, j=W; 
	while (! (i==n-1 && j==0))
	{
		if(j-sizes[i]>=0 &&matrix[i][j] == matrix[i+1][j-sizes[i]] + values[i]){
			taken[i]=1;
			j=j-sizes[i];
			i=i+1;
		}else
		{
			taken[i]= 0;
			i++ ;
		}
	}

	return matrix[0][W];
}


int main(){

	/*
	example 1 
	word1 = "horse", word2 = "ros"
	Output: 3
	Explanation: 
	horse -> rorse (replace 'h' with 'r')
	rorse -> rose (remove 'r')
	rose -> ros (remove 'e')
	*/
	string word1 = "horse";
	string word2 = "ros" ;
	cout << minDistance(word1,word2)<<endl;

	/*
	word1 = "intention", word2 = "execution"
	Output: 5
	Explanation: 
	intention -> inention (remove 't')
	inention -> enention (replace 'i' with 'e')
	enention -> exention (replace 'n' with 'x')
	exention -> exection (replace 'n' with 'c')
	exection -> execution (insert 'u')
	*/
	word1 = "intention";
	word2 = "execution" ;
	cout << minDistance(word1,word2)<<endl;
	cout<< "*******************************************" << endl;
	////////////////////////////////////////////


	// Knapsack problem !
	// ex1 at https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html
	vector<int> values;
	values.push_back(92);
	values.push_back(57);
	values.push_back(49);
	values.push_back(68);
	values.push_back(60);
	values.push_back(43);
	values.push_back(67);
	values.push_back(84);
	values.push_back(87);
	values.push_back(72);


	vector<int> weight;
	weight.push_back(23);
	weight.push_back(31);
	weight.push_back(29);
	weight.push_back(44);
	weight.push_back(53);
	weight.push_back(38);
	weight.push_back(63);
	weight.push_back(85);
	weight.push_back(89);
	weight.push_back(82);

	int W = 165;
	
	vector<bool> taken(weight.size(),0);
	
	cout << knapSack(W,weight,values,taken) << endl ;;
	for (int i = 0; i < taken.size(); i++)
	{
		cout<< taken[i] << " " ;
	}

	system("pause");
}