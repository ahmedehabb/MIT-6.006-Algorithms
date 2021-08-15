#include <iostream>
#include <vector>
using namespace std ;



int getMax(vector<int> arr){
	int max =abs(arr[0]) ;
	for(int i=0;i<arr.size();i++){
		if(abs(arr[i])>max)
			max=abs(arr[i]);
	}
	return max; 
}



vector<int> countingSort( vector<int> arr){
	// assuming we will sort integers only (not object with other stuff)
	
	// assume also that range of numbers are from [0,k-1] 
	// this k cant be too large ,it must be O(n) -->  in order to maintain O(n) complexity for whole Algorithm
	
	// make vector of size k if max k-1 
	// so 
	int k =getMax (arr) ;
	vector<int> count(k+1); 

	// so now we will save count of each key in count[key]  
	for(int i=0; i<arr.size(); i++){
		count[ arr[i] ] ++ ;
	}


	// now we need to know how much elements really exists
	// iknow max but real elements could be much less
	// ex k=9 and input  = 1 5 8 7 2 1 -> so these are real elements only not 0->8

	// so we will make cumulative count of the vector "count" as it contain count of each element 
	for(int i=1 ; i< count.size() ; i++){
		count[i] = count[i] + count[i-1] ;
	}

	// now count[end]= count[ count.size() -1 ] contain real count of items 
	vector<int> sorted(count[count.size() -1 ]) ;
	
	// so now for ex count array is cumulative 
		//as for ex 0 1 1 3 3 4 5 5 6
	// so sorted vector is of size 6 -> this mean last index = 5
	// when making sorted array 
	
	// we take cumulative freq of arr[i] as an index for sorted array --> sorted [ count[ arr[i] ] ] 
	// and put arr[i] in that index and then decrement count[arr[i]]
	// but Take Care -->
			//here in our example 
			// we could make sorted [ count[ arr[i] ] ]  = sorted[6] so this could do an error since its out of index 
			// so we will de predecrement to assure right index 

	for(int i=0; i<arr.size(); i++){
		sorted [ --count[arr[i] ] ] = arr[i] ;
	}

	return sorted ;
}



void countingSortByDigit( vector<int> &arr , int exp , vector<int> &indices){
	

	// count here will be at max of size 10 since we sort acc to digits
	vector<int> count(10);

	// so now we will save count of each key in count[key]  
	// but we will take in consideration exp 
	// if exp =1 this mean we order by unit digit only, if 10 -> tenth and so on 
	for(int i=0; i<arr.size(); i++){
		count[ (abs(arr[i])/exp)%10 ] ++ ;
	}


	// now we need to know how much elements really exists
	// iknow max but real elements could be much less
	// ex k=9 and input  = 1 5 8 7 2 1 -> so these are real elements only not 0->8

	// so we will make cumulative count of the vector "count" as it contain count of each element 
	for(int i=1 ; i< count.size() ; i++){
		count[i] = count[i] + count[i-1] ;
	}

	// now count[end]= count[ count.size() -1 ] contain real count of items 
	vector<int> sorted(count[count.size() -1 ]) ;
	
	// so now for ex count array is cumulative 
		//as for ex 0 1 1 3 3 4 5 5 6
	// so sorted vector is of size 6 -> this mean last index = 5
	// when making sorted array 
	
	// we take cumulative freq of arr[i] as an index for sorted array --> sorted [ count[ arr[i] ] ] 
	// and put arr[i] in that index and then decrement count[arr[i]]
	// but Take Care -->
			//here in our example 
			// we could make sorted [ count[ arr[i] ] ]  = sorted[6] so this could do an error since its out of index 
			// so we will de predecrement to assure right index 


	// TAKE CARE
	// VI NOTE --> WE MUST DO BACKWARD LOOP 
	// SINCE IF WE MAKE FORWARD LOOP AND we sort now by tenth digit 
			//-> so all unit digits will be at count[0] --> #unit digits for ex = 9 -> count[0] =9
			// so if for loop is forward count[ (arr[i]/exp)%10 ] = count[0] = 9
				// so sorted[9] = arr[i] = arr[0] = 0 
				// so sorted[8] = arr[i] = arr[1] = 1 
				// so sorted[0] = arr[i] = arr[9] = 9
				// so sorted [0..9] = 9 ....1 0 so incorrect
				// this mean the loop will put unit digit- sorting descendingly

	vector<int> indicesTemp(count[count.size() -1 ]) ;


	for(int i=arr.size() -1; i>=0; i--){
		sorted [ count[ (abs(arr[i])/exp)%10 ] -1] = arr[i] ;
		indicesTemp[ count[ (abs(arr[i])/exp)%10 ] -1] = indices[i] ;
		count[ (abs(arr[i])/exp)%10 ] -- ;
	}

	// here we must return original array sorted -> as we will call function many times on arr so we need to update arr itself 
		for(int i=0; i<arr.size(); i++){
			arr[i] = sorted[i] ;
			indices[i]=indicesTemp[i];
		}

}




void radixSort(vector<int>& arr,vector<int>& indices){
	// imagine we want to break each integer as base b 
	// so for number k
		// #digits (d) = (logk for base b) + 1 

	// Algorithm works as follows 
		// sort integers by least significant digit
		//  .. 
		//	..
		//  ..
		// sort integers by most significant digit

	// Each of these sorts will be done using counting sort. 

	// Complexity  = O(n+b) for each digit 
	// Overall Complexity  = O( d(n+b) ) = O(nC)



	// we need to know max number in arr so as to know how many digits 
	int max = getMax(arr) ;

	for (int exp = 1; abs(max)/exp> 0 ; exp*=10 )
	{
		countingSortByDigit(arr,exp,indices) ;
	}
	
}


    int binarySearch(vector<int>& A,int first,int last, int target){
        if(first>last)
            return -1;
        
        int mid = (last- first)/2 ;
        if(target ==A[first + mid]){
            return first+mid ;
        }else if(target <A[first+ mid]){
            return binarySearch(A,first,first+mid-1,target);
        }else
        {
            return binarySearch(A,first+mid+1,last,target);
        }
        
    }


 vector<int> twoSum(vector<int>& nums, int target) {

	 // since we could have pos and neg numbers 
	 // so to sort them -> i sorted each of them separately since our normal radix sort doesnt support -ve numbers
	 
	 // To sort neg Numbers
		// i only cared about abs(values) and act as if they were positive
		// so if arr =  -10 -5  -21
		// i act as if its -> 10 5 21
		// but output is [ 5 10 21] -> so i put that in reverse order so it will be (-21 -10 -5)


	 // VI NOTE 
		// that i made negIndices, posIndices -> where i pass real indices of the items in there 
		// and change both of them while sorting 
		// example : if Array : [-21 55 7 10 -4]
			// so Initially
				// pos array : [55 7 10] , posInd : [1 2 3]
				// neg array : [-21 -4] , negInd : [0 4]
			// after sorting
				// pos array : [7 10 55] , posInd : [2 3 1]
				// neg array : [-4 -21] , negInd : [4 0] --> remember i sort them as pos numbers then handle that

	vector<int> neg ,negIndices;
	vector<int> pos ,posIndices;

	for(int i=0;i<nums.size();i++){
		if(nums[i]< 0){
			neg.push_back(nums[i]);
			negIndices.push_back(i);
		}else{
			pos.push_back(nums[i]);
			posIndices.push_back(i);
		}
	}


	if(neg.size()!=0)
		radixSort(neg,negIndices);
	if(pos.size()!=0)
		radixSort(pos,posIndices);


	// here is combining both pos and neg parts of main array ->
	vector<int> indices(nums.size()) ;

	// notice that i fill neg ones from back to forth as i said above
	for(int i=0;i<neg.size();i++){
		nums[i]=neg[ neg.size()-i-1];
		indices[i]= ( negIndices[neg.size()-i-1]) ;
	}

	// filling pos 
	for(int i=neg.size(),j=0;i<nums.size();j++,i++){
		nums[i]= pos[j] ;
		indices[i] = posIndices[j];
	}

	    vector<int> Target ;

		// Main goal of sorting that 
			// i made one for loop and i have arr[i] and target
			// main objective to find y where :: arr[i] + y = target
			// therefore we could do BinarySearch on y where y = target - arr[i]
			// and if found return them
        for(int i=0; i<nums.size();i++){
            int y=binarySearch(nums,0,nums.size()-1,target - nums[i]);
            if(y!=i && y!= -1 ){
                Target.push_back(indices[i]);
				Target.push_back(indices[y]);
                return Target;
            }
        }
    return Target;
    }
    

int main (){

	vector<int> arr ;

	arr.push_back(-2489365); 
	arr.push_back(-993808); 
	arr.push_back(2489365); 
	arr.push_back(993808); 
	//arr.push_back(7677553); 

	// this problem is called twoSum in leetCode you could find it in website
	// Problem :Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
	// you could easily solve it using O(n^2) but its not better solution
	// for more better solution you could sort the array but you must save the original indices and change them while you sort
	// as output : is to find original indices of 2 elements giving that target

	// in Order to know difference between this solution and nested loop solution 
	// nested loop time : 364 ms -- while that solution : 20 ms only

	// you Could even do better using hash tables -- Try it.

	// Ok so Our Algorithm 
		// 1. Sort the array of numbers[pos,neg] using radix sort
		// Ok why ????
			// Main goal of sorting that 
			// to make one for loop instead of two 
			//so for each loop i have arr[i] and a target
			// MAIN OBJECTIVE : 
				//to find y where :: arr[i] + y = target
				// therefore we could do BinarySearch on y where y = target - arr[i]
				// and if found return them
	
	vector<int> tar =twoSum(arr,-3483173);

	for( int i = 0 ; i<tar.size() ; i++){
		cout << tar[i] << " " ; 
	}
	cout << endl ;
	
	
	
	system("pause") ;
}