#include <iostream>
using namespace std; 
#include<vector>


// defining 1Dpeak problem :
	// the value is peak iff its larger than its left and right neighbours 
	// for one sided values you have to check only the one neighbour they have

//Try it yourself :: Proof Each 1D array has a peak ?


int OneD_peakfinding(vector<int> myArray , int firstIndex, int lastIndex){
	// we could solve it using O(n^2) algorithm by nested-for loops but its bad practice
	// so Our algorithm 
		// 1. get middle value
		// 2. compare it with its neighbours 
		//			if > both neighbours we're done
		//			else we will recursively solve halves of the problem depending on in which half neighbour is greater
	
	int size = lastIndex - firstIndex + 1; 
	
	int mid = (size -1 )/2 ;
	
	// no neighbours 
	if(size ==1)
		return myArray[0]; 

	// having only 1 right neighbour // note we cant have left neighbour only as our mid will always be on left 
	if(mid+1 == size - 1 && mid-1 <0) 
		return max(myArray[firstIndex + mid],myArray[firstIndex + mid + 1]) ;
	// note i'm using "firstIndex +" as i will be passing the same array without slicing or modifying it so i must know which is first element exactly
	// not just myArray[mid] due to recursion calls


	// having 2 neighbours (normal case)
	if ( myArray[firstIndex + mid] < myArray[firstIndex + mid + 1] )
		return OneD_peakfinding(myArray,firstIndex + mid + 1, lastIndex);
	else if ( myArray[firstIndex + mid] < myArray[firstIndex + mid - 1] )
		return OneD_peakfinding(myArray,firstIndex, firstIndex + mid - 1);
	else
		return myArray[firstIndex + mid]; 

}




int main () {

	vector<int> myArray;
	myArray.push_back(1);
	myArray.push_back(3);
	myArray.push_back(4);
	myArray.push_back(6);
	myArray.push_back(8);
	myArray.push_back(10);
	myArray.push_back(11);
	myArray.push_back(10);

	int peak = OneD_peakfinding(myArray , 0,myArray.size()-1 ) ; 
	cout <<"1D peak is " << peak << endl ;

	system("pause"); 
}