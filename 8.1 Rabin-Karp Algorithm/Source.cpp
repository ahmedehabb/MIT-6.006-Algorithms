#include <iostream>
using namespace std; 
#include<string.h>
#include<vector>

// naive string matching [ substring p in whole text t ]
vector<int> naiveStringMatching(string p, string t){
	// naive solution is to go through all substring of size= size of p and figure if they match or not
	// let [p] = size of p for illustration
	// # possible substrings = [t] - [p] +1
	// because if you find p 
			//--> first possible location is index 0 till m-1
			//--> last possible location to find p in t is n-m  till n-1
			// so #possible substring of size p = ( (n-m) - (0) +1) 

	vector<int> indices ;
	for(int i=0; i< t.size() - p.size() +1 ;i++){
		// t.substr(pos,length)  take substring of t from index pos of size=length  

		// .compare return 0 if strings are equal
		if(p.compare(t.substr(i, p.size())) ==0 ) {
			indices.push_back(i) ;
		}
	}
	return indices ;

}


//Rabin-Karp

// https://stackoverflow.com/questions/15945401/prime-number-and-block-length-in-karp-rabin
// better see this : help in understanding choice of prime-number-and-block-length-in-karp-rabin

// p : substring
// t : whole text
// q : prime
vector<int> Rabin_Karp(string p, string t, int q) { 

	//We are looking for a pattern P[1…m] in a string S[1…n]. 
	//The Rabin-Karp algorithm does this by defining a hash function h. 
	//We compute h(P) (that is, the hash of the pattern), 
	//and comparing it to h(S[1…m]), h(S[2…m+1]) and so on. 
	//If we find a matching hash, then it is a potential matching substring.
	// This is called a "rolling hash". 

	// we will be computing hash of substring from previous one
	// subHash = (d*(subHash - txt[i]*h) + txt[i+M])%q;
	// subHash of new one = d*(oldsubhash - higherchar in old substring *h) + new lower char to be included

	//choosing q: prime no. to be used in hash Function
	// The maximal value of t[i] is d-1
	// h can be as large as q-1 ( h= ( d^m-1) mod q )
	// So if (q-1)*(d-1)*d > INT_MAX --> That limits the size of the prime that can be safely chosen to INT_MAX/(d*(d-1)) + 1.

	// so must take care of your prime no. choice
	
	// vector containing indices of occurence of p in t 
	vector<int> indices ;

	int n = t.size() ;
	int m = p.size() ;

	
	// d is the number of characters in the input alphabet
	int d= 256;
	
	 // The value of h would be "pow(d, M-1)%q"
	int h = pow(d,p.size()-1) ;
	h = h% q ;

	int phash = 0; // hash value for pattern
    int thash = 0; // hash value for txt


	// preprocessing : calculating hash of p which wouldnt change 
	// and calculating first window of t; 
	for (int i = 0; i < m; i++)
	{
		phash = (d*phash + p[i]) % q ;
		thash = (d*thash + t[i]) % q ;
	}

	for (int i = 0; i < n-m+1; i++)
	{
		if(phash == thash){
			// this doesnt say that p==t[i..i+m]
			// since they could have same hash value but still not same string-> called spurious hit
			// so we must do furthur checking

			if(p.compare(t.substr(i, p.size()))==0 ) {
				indices.push_back(i) ;
			}
		}

		
		if(i< n-m ) { // not to overflow
			// tHash = (d*(subHash - txt[i]*h) + txt[i+M])%q;
			thash = ( d*( thash - t[i]*h) + t[i+m] ) % q ;

			// We might get negative value of t, converting to positive
            if (thash< 0)
				thash = thash + q;
		}
	}

	return indices ;
}

int main(){

	// naive ;
	string t= "abaaccaac";
	string p ="aac";
	
	//vector<int> indices = naiveStringMatching(p,t);
	//for(int i=0;i<indices.size();i++){
	//	cout << indices[i] << endl ;
	//}

	// rabin-karb
		
	vector<int> indices2 = Rabin_Karp(p,t,101);
	for(int i=0;i<indices2.size();i++){
		cout << indices2[i] << endl ;
	}


	system("pause");
}