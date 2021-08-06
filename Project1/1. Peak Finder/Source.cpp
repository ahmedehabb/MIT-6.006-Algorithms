#include <iostream>
using namespace std; 
#include<vector>


// defining 1Dpeak problem :
	// the value is peak iff its larger than its left and right neighbours 
	// for one sided values you have to check only the one neighbour they have

//Try it yourself :: Proof Each 1D array has a peak ?
int OneD_peakfinding(vector<int> myArray , int firstIndex, int lastIndex , int &foundIndex){
	// we could solve it using O(n^2) algorithm by nested-for loops but its bad practice
	// so Our algorithm 
		// 1. get middle value
		// 2. compare it with its neighbours 
		//			if > both neighbours we're done
		//			else we will recursively solve halves of the problem depending on in which half neighbour is greater
	
	int size = lastIndex - firstIndex + 1; 
	
	int mid = firstIndex + (size -1 )/2 ;
	// note i'm using "firstIndex +" as i will be passing the same array without slicing or modifying it so i must know which is first element exactly
	// not just myArray[mid] due to recursion calls


	// no neighbours 
	if(size ==1){
		foundIndex =firstIndex ;
		return myArray[firstIndex]; 
	}
	// having only 1 right neighbour // note we cant have left neighbour only as our mid will always be on left 
	if(mid+1 == size - 1 && mid-1 < 0){ 
		foundIndex = myArray[mid] > myArray[mid + 1] ?  mid : mid+1 ;
		return max(myArray[mid],myArray[mid + 1]) ;
	}


	// having 2 neighbours (normal case)
	if ( myArray[ mid] < myArray[mid + 1] )
		return OneD_peakfinding(myArray, mid + 1, lastIndex,foundIndex);
	else if ( myArray[mid] < myArray[mid - 1] )
		return OneD_peakfinding(myArray,firstIndex, mid - 1,foundIndex);
	else
	{
		foundIndex = mid ;
		return myArray[mid]; 
	}
}



// defining 2Dpeak problem :
	// the value is peak iff its larger than all its neighbours from up , left , down , right
int TwoD_peakfinding(vector<vector<int>> myMatrix, int firstRow, int lastRow , int firstCol,int lastCol){
	
	// First of All take care here of matrix[][] 
	// My taken convention that the first place is for columns then each element has rows down to it
	// its same if you changed and treated it as rows then cols 


	// we could solve it using O(nm) algorithm for n rows, m cols by nested-for loops but its bad practice
	// so Our algorithm 
		// 1. get middle column
		// 2. get 1d peak in that col -> log(m) 
			// there is another type which we can get global max but above is better as max is O(m) so we can do better
		// 3. check neighbours to right and left only since we checked up,down in 1d peak algo in step 2 

		// 4. if left > got value -> solve recursively left cols 
		//    else if right > got value -> solve recursively right cols 
		//	  else we got peak as its > all its neighbours 

		int cols = lastCol - firstCol + 1; 
		int rows = lastRow - firstRow + 1;

		int midColumn = firstCol + (cols-1) /2 ; 
		
		// foundIndexInColumn is row where 1d peak is found in midcolumn
		int foundIndexInColumn = -1 ;
		int oneDPeak = OneD_peakfinding (myMatrix[midColumn], 0 , rows - 1,foundIndexInColumn) ;
		
		// comparing the 1dpeak i got but we need the index of oneDPeak value in column 
		// if left is > , so will take left cols
		if(midColumn-1 >=0 && myMatrix[midColumn-1][foundIndexInColumn] >  myMatrix[midColumn][foundIndexInColumn] )
		{
			return TwoD_peakfinding(myMatrix,firstRow , lastRow  ,firstCol ,midColumn-1 ) ;
		}
		else if (midColumn+1 < cols && myMatrix[midColumn+1][foundIndexInColumn] >  myMatrix[midColumn][foundIndexInColumn] )
		{
			return TwoD_peakfinding(myMatrix, firstRow , lastRow  ,midColumn+1, lastCol ) ;
		}
		
		// if its greater than both return it 
		return myMatrix[midColumn][foundIndexInColumn] ;
}


int main () {

	/*
	1D EXAMPLE :: 

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
	*/

	vector<vector<int>> myMatrix ;

	// i will insert vectors as columns as i worked on that if you need to insert rows its ok but you may need to change function
	vector<int> col1,col2,col3,col4,col5;
	col1.push_back(0);
	col1.push_back(0);
	col1.push_back(0);
	col1.push_back(0);
	col1.push_back(0);

	col2.push_back(3);
	col2.push_back(4);
	col2.push_back(5);
	col2.push_back(6);
	col2.push_back(7);

	col3.push_back(2);
	col3.push_back(1);
	col3.push_back(0);
	col3.push_back(0);
	col3.push_back(8);

	col4.push_back(0);
	col4.push_back(0);
	col4.push_back(0);
	col4.push_back(0);
	col4.push_back(0);

	col5.push_back(0);
	col5.push_back(0);
	col5.push_back(0);
	col5.push_back(0);
	col5.push_back(0);

	myMatrix.push_back(col1);
	myMatrix.push_back(col2);
	myMatrix.push_back(col3);
	myMatrix.push_back(col4);
	myMatrix.push_back(col5);


	int twoDpeak = TwoD_peakfinding(myMatrix,0,4,0,4);
	cout << twoDpeak << endl ;

	system("pause"); 
}