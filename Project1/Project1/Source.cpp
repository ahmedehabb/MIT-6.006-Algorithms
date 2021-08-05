#include <iostream>
using namespace std; 
#include<vector>


// defining 1Dpeak problem :
	// the value is peak iff its larger than its left and right neighbours 
	// for one sided values you have to check only the one neighbour they have

//Try it yourself :: Proof Each 1D array has a peak ?


int OneD_peakfinding(vector<int> myArray){
	// we could solve it using O(n^2) algorithm by nested-for loops but its bad practice
	// so Our algorithm 
		// 1. get middle value
		// 2. compare it with its neighbours 
		//			if > both neighbours we're done
		//			else we will recursively solve halves of the problem depending on which half is greater




}




int main () {




	system("pause"); 
}