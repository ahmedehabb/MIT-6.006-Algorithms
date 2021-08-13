#include<iostream>
using namespace std; 

#include "AVLTree.h"

int main(){

	int keys[] = {41,20,65,50,11,23,26,29,55};
	// this ensure 2 cases (do 1 rotation when inserting 29 , do 2 rotations when inserting 55 ) ;

	AvlTree myTree;

	for(int key:keys){
		myTree.insert(key) ;
	}

	
	


	system("pause");
}