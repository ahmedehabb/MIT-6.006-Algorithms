#include <iostream>
using namespace std; 


#include"HashTable.h"

int main(){

	
	// using divisionMethod -> we need to choose [m] wisely
	// must be prime number , away from powers of 2 -> 
	HashTable myHashTable_division(101) ;
	myHashTable_division.insert_Division(1);
	myHashTable_division.insert_Division(15);
	myHashTable_division.insert_Division(81);
	myHashTable_division.insert_Division(41);
	myHashTable_division.insert_Division(60);
	myHashTable_division.insert_Division(21);
	myHashTable_division.insert_Division(9);
	myHashTable_division.insert_Division(11);
	myHashTable_division.insert_Division(55);
	myHashTable_division.insert_Division(84);
	myHashTable_division.insert_Division(61);
	myHashTable_division.insert_Division(70);
	myHashTable_division.insert_Division(31);
	myHashTable_division.insert_Division(49);
	
	Node<int>* found= myHashTable_division.searchKey_Division(9);
	found=myHashTable_division.searchKey_Division(22);
	found=myHashTable_division.searchKey_Division(21);
	found=myHashTable_division.searchKey_Division(82);
	found=myHashTable_division.searchKey_Division(81);


	// using multiplicationMethod -> we dont need to be as careful as previous case
	// when choosing m since constant A -> helps in randomization more
	HashTable myHashTable_multiplication(101) ;
	myHashTable_multiplication.insert_Multiplication(1);
	myHashTable_multiplication.insert_Multiplication(15);
	myHashTable_multiplication.insert_Multiplication(81);
	myHashTable_multiplication.insert_Multiplication(41);
	myHashTable_multiplication.insert_Multiplication(60);
	myHashTable_multiplication.insert_Multiplication(21);
	myHashTable_multiplication.insert_Multiplication(9);
	myHashTable_multiplication.insert_Multiplication(11);
	myHashTable_multiplication.insert_Multiplication(55);
	myHashTable_multiplication.insert_Multiplication(84);
	myHashTable_multiplication.insert_Multiplication(61);
	myHashTable_multiplication.insert_Multiplication(70);
	myHashTable_multiplication.insert_Multiplication(31);
	myHashTable_multiplication.insert_Multiplication(49);
	
	found=myHashTable_multiplication.searchKey_Multiplication(1);
	found=myHashTable_multiplication.searchKey_Multiplication(12);
	found=myHashTable_multiplication.searchKey_Multiplication(13);
	found=myHashTable_multiplication.searchKey_Multiplication(15);
	found=myHashTable_multiplication.searchKey_Multiplication(41);
	found=myHashTable_multiplication.searchKey_Multiplication(9);

	myHashTable_multiplication.deleteKey_Multiplication(1);
	myHashTable_multiplication.deleteKey_Multiplication(12);

	found=myHashTable_multiplication.searchKey_Multiplication(1);
	found=myHashTable_multiplication.searchKey_Multiplication(12);


	system("pause");
}