#include <iostream>
using namespace std; 


// normal insertion sort
int* InsertionSort(int* A , int size){
	// we will start by second element compare it with first element and if smaller do pairwise swap
	// and continue to third element compare it with second element and do pairwise if smaller and compare it with 1st and  do pairwise if smaller
	// and so on 

	// if current element > one before it we will ski since that all elements before current are already sorted !

	if (size ==1)
		return A; 

	int key = 0 ; 

	for (int i =1 ; i<size ; i++){
		
		key = A[i]; 
		int currentIndex= i ; // points to current element 
		// we need to keep track as if we made more than 1 swap we will need to decrement it 

		for(int j = i-1 ; j>=0 ; j--){
			if(key >A[j])
				break ; 
			else
			{
				// we will swap 
				A[currentIndex]=A[j]; 
				A[j] = key ;
				currentIndex-- ;
			}
		}
	}
	return A; 
}

// binary search return the correct index to put a given value in it
// note that this assume Array A to be sorted
int binarySearch(int *A, int first,int last, int value){
	
	int size = last - first + 1; 

	if(size == 0)
		return first ;

	int mid = ( (size-1) / 2 ) + first; // we need to add first since mid is computed only depending one size 
	// so if array 1 2 3 4 and we now work on right half (3 4) the mid would've been be (size-1/2 )= 0 which is incorrect so we need to add first index "2" 

	// if value == A[mid] we will say that we will put it after the mid item for my convention
	if(value == A[mid]){
		return mid+1 ; 
	}

	if(value < A[mid]){
		return binarySearch(A,first , mid-1 , value) ;
	}else if(value > A[mid]){
		return binarySearch(A,mid+1, last , value) ;
	}

}

// binary insertion sort
int* BinaryInsertionSort(int* A , int size){
	// its similar to normal insertion sort but 
	// it depends on the idea that A[0..i-1] is sorted
	// here we dont make pairwise swaps but do binary search in the sorted part A[0..i-1]
	// and know the right location of right element and then do shifting operations

	if (size ==1)
		return A; 

	int key = 0 ; 

	for (int i =1 ; i<size ; i++){
		
		key = A[i]; 
		int currentIndex= i ;

		int rightIndex = binarySearch(A,0,i-1 , key) ; // we will search in the sorted part for right location

		// now we need to do shift operations 
		// #items to be shifted = current index - right index ;
		// example : 1 4 6 2 and we need to put 2 in its rigt index
		// current index = 3 , right index =1 --> 3-1=2 items to be shifted (4,6) 


		// our loop starts from the index before me till i reach rightIndex
		// therefore #items to be shifted = current index - right index ;
		for( int j= currentIndex-1 ; j>=rightIndex ; j--){
			
			A[j+1] = A[j] ;
			A[j] = key ;
		}
	}
	return A; 
}



// Merge Sort

// Merge function takes 2 sorted arrays as input
// return merged sorted array 

int* Merge(int*left , int* right, int leftSize, int rightSize){
	
	// we will have 2 pointers to indexes of both arrays 
	int leftPointer = 0 ;
	int rightPointer = 0 ;

	if(leftSize ==0)
	{
		// we will return right Array as it is;
		return right ;
	}
	else if(rightSize==0)
	{
		// we will return left Array as it is;
		return left ;
	}


	int * Merged = new int[leftSize+rightSize ];
	int mergedIndex = 0 ; // points to first item in merged array

	for( int i = 0 ; i< leftSize+rightSize ; i++){
		
		// here we will compare the items in both arrays where we are pointing to 
		// if one pointer exceeded boundary --> means that we took all elements in the array
				// we will append the other array to the full array ; 
				//Note : we will check that at the beginning 

		if(leftPointer == leftSize ) { // we will append right array
			// we could do for loop puting them all then exit and we can just put one by one 
			// i'll do for loop instead of comparing each loop -> if(leftPointer == leftSize )

			for( int j= rightPointer ; j<rightSize ; j++)
			{
				Merged[mergedIndex] = right[j] ; 
				mergedIndex ++ ;
			}
			break ; 	
		}
		else if(rightPointer == rightSize){ // same but for the other array
			for( int j= leftPointer ; j<leftSize ; j++)
			{
				Merged[mergedIndex] = left[j] ; 
				mergedIndex ++ ;
			}
			break ; 
		}
		else{
			// this is the general case where left and right are still valid to use
			// we will put smaller one in merged array and increment its pointer 

			if(left[leftPointer] < right[rightPointer] ){
				Merged[mergedIndex] = left[leftPointer] ; 
				mergedIndex ++ ;
				leftPointer ++ ;
			}
			else if( left[leftPointer] > right[rightPointer] ){
				Merged[mergedIndex] = right[rightPointer] ; 
				mergedIndex ++ ;
				rightPointer ++ ;
			}
			else{
				// if both are equal we could take any of them and enter loop again
				// but its not the best solution since next loop the one which is not taken will be taken 
				// so we could take both at a single time

				Merged[mergedIndex] = right[rightPointer] ;
				mergedIndex ++ ;

				Merged[mergedIndex] = left[leftPointer] ; 
				mergedIndex ++ ;
				
				// incrementing both ptrs 
				leftPointer ++ ;
				rightPointer ++ ;
			}
		}
	}

	return Merged ; 
}


int* MergeSort(int* A, int size ){

	// since its divide and conquer algorithm
		// we will keep dividing Array into 2 arrays till we reach leaves (1 sized array)
		// then merge leaves into arrays of size 2 -> then merge these arrays into ones of size =4 and so on 

	// so this is our base case where we reach leaves level 
	if(size == 1)
		return  A; 


	int mid = (size-1) /2 ; 
	

	// Making the 2 Arrays (left , right ) 

	// left will be 0..mid -> mid+1 items
	int leftSize = mid+ 1 ;
	int * left = new int [leftSize];  
	// note that we need to copy items without dependency on original "A"
	// not just passing A[0.. mid]
	for (int i = 0 ; i<leftSize ; i++){
		left[i] = A[i] ;
	}
	// we will recursively call mergeSort on this left partition untill we sort it  
	left = MergeSort(left,leftSize);
	
	// right will be mid+1 .. last(size - 1 )
		// so #items = last - first + 1 = size -1 - (mid+1) +1 = size - mid -1
	int rightSize = size - mid - 1;

	int * right = new int [rightSize];  
	for (int i = 0 ; i< rightSize ; i++){
		right[i] = A[i+ mid + 1] ;
	}

	// we will recursively call mergeSort on this right partition untill we sort it 
	right = MergeSort(right , rightSize);

	
	// Merging 
	return Merge(left,right,leftSize,rightSize ) ;

}



int main(){

	int  A1[] = {1,6, 5, 2,4,7,8,5};
	int  A2[] = {1,6, 5, 2,4,7,8,5};
	int  A3[] = {1,6, 5, 2,4,7,8,5};
	
	
	int * B= MergeSort(A1,8) ;
	int * C= InsertionSort(A2,8) ;
	int * D = BinaryInsertionSort(A3,8);

	cout << "Merge Sort {1,6, 5, 2,4,7,8,5}  " << endl ;
	cout << "Output : " ; 
	for( int i =0 ; i<8; i++){
		cout << B[i] << "  " ;
	}
	
	cout << endl ;
	cout << " ****************************************" << endl ;
	cout << "InsertionSort{1,6, 5, 2,4,7,8,5}  " << endl ;
	cout << "Output : " ; 

	for( int i =0 ; i<8; i++){
		cout << C[i] << "  " ;
	}
		
	cout << endl ;
	cout << " ****************************************" << endl ;

	cout << "BinaryInsertionSort{1,6, 5, 2,4,7,8,5}  " << endl ;
	cout << "Output : " ; 
	for( int i =0 ; i<8; i++){
		cout << D[i] << "  " ;
	}
	cout << endl ;
	system("pause");
}