#include<iostream>
#include <vector>
#include<unordered_map>
using namespace std;

 vector<int> twoSum(vector<int>& nums, int target) {
     // our hash table will be {key : index}
     unordered_map<int, int> map;
     vector<int> result ; 
    
     for(int i=0; i<nums.size() ; i++){
         // to check if key exists
         if(map.find(target-nums[i])!= map.end() ) {
             result.push_back(i);
             result.push_back(map[target-nums[i]] );
             return result;   
        }else
        {
            map[nums[i]]= i ;

        }
     }
     
     return result; 
 }    


 int main() {

	 // Runtime: 4 ms, faster than 99.58% of C++ online submissions for Two Sum.
	//  Memory Usage: 10.9 MB, less than 38.85% of C++ online submissions for Two Sum.
	// info about this solution by Me at leet code
	 // Go see Radix sort Lecture 7 where we solved this in 20ms which was better than O(n^2) nested loop
	 // however this is the best solution outthere

	 vector<int> nums; // {2,7,11,15}
	 nums.push_back(2);
	 nums.push_back(7);
	 nums.push_back(5);
	 nums.push_back(9);
	 int target = 9 ;

	 twoSum(nums,target) ;

	 system("pause") ;
 }