#include <iostream>
using namespace std; 


void maxHeapify(int*A, int index, int size){
	int left = 2* index +1 ;
	int right = 2* index + 2;
 
	if(left >= size && right>=size) // this means its leaf node and doesnt have any child
		return ; 

	// we made a very important assumption that left and right subtrees must be max heaps 
	// so we could only have 1 incorrect position and need to fix it not more than 1 
	

	// checking if only one child exists
	if(left < size && right >= size){
		if(A[index] < A[left]){
			int temp  = A[index] ; 
			A[index] = A[left] ;
			A[left] = temp ; 
			maxHeapify(A,left,size) ;
		}
	}
	else if(right < size && left >= size){
		if(A[index] < A[right]){ // so right should be root 
			int temp  = A[index] ; 
			A[index] = A[right] ;
			A[right] = temp ; 
			maxHeapify(A,right,size) ;
		}
	}
	else // if both left and right children exists
	{
		// first we must get max of them as we will swap with maximum one 
		if(A[left]>A[right] && A[index] < A[left]) // if left> right so take it but must also be > root
		{
			// we must check that A[index] smaller than left to change them
				int temp  = A[index] ; 
				A[index] = A[left] ;
				A[left] = temp ; 
				maxHeapify(A,left,size) ;
			
		}else if (A[right]>A[left] && A[index] < A[right])
		{
			
				int temp  = A[index] ; 
				A[index] = A[right] ;
				A[right] = temp ; 
				maxHeapify(A,right,size) ;
		}
	}
}


void buildHeap(int*A, int size){
	
	// here we start from size/2 since from [ size/2 + 1 .... end] these all are leaves 
	// and leaves are max heaps by definition
	for(int i=size/2 ; i>=0 ; i--){
		maxHeapify(A,i,size) ;
	}
}

void heapSort(int*A, int size){
	if(size<=1 ) 
		return ; 

	int tempSize = size; // we need to save real size in a temp .. why ? 
	// as if not we will decrement it inside the loop and so the #iterations is incorrect

	for (int i = 0 ; i < tempSize ; i++){
		
		int max = A[0] ;  // since its max heap 
		// swapping max element with last element in array 
		A[0] = A[size-1] ; 
		A[size-1 ] = max ; 
		
		size -- ;  //  decrementing size each loop as we put max element in last index each time so if we take it 
		// and dont dec our size we will have wrong answers as our algorithm assume left and right subtrees are max heaps already

		// generally now our heap is not max heap since root isnt max 
		maxHeapify(A,0,size) ;
	}
}

int main() { 

	int A[] = {1,5,6,8,0,10,20} ;

	buildHeap(A,7) ; 

	heapSort(A,7) ;

	for(int i = 0 ; i< 7 ; i++){
		cout << A[i] << " " ; 
	}
	cout << endl  ;
	system("pause");
}