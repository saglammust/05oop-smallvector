/*
Name: Mustafa Sa�lam
ID: 150140129
20.03.17
*/
#include<iostream>
#include"SmallVector.h"

void printSmallVector(const char* const message, const SmallVector& in_vector) { 
	std::cout << message << ": "; 
	for (int i = 0; i < in_vector.getSize(); i++) {
		std::cout << in_vector[i] << " ";
	} 
	std::cout << std::endl;
}

int main()
{
	int temp[35]; 
	for (int i = 0; i < 35; i++) { 
		temp[i] = i;
	} 
	SmallVector test(temp, 10); // Creating SmallVector with 10 elements
	SmallVector test2(temp, 35);// Creating SmallVector with 35 elements
	printSmallVector("Printing test in reverse", test.reverse()); // print test in reverse order
	SmallVector test3; // Empty
	test3 = test2 + test; // Concatenate two SmallVectors
	printSmallVector("Printing test3", test3);
	SmallVector test4(test); // Copy SmallVector
	SmallVector test5(temp, 2);
	test5 = test5 * 5; // Replicate elements
	test5.push_back(12); // Add 12 at the end
	test5[0] = 4; // Modify the first element of test5
	std::cout << "Printing test5 in reverse: ";
	for (int i = 1; i < test5.getSize() + 1; i++) {// Testing negative numbers as indices
		std::cout << test5[-i] << " ";
	}
	std::cout << std::endl;
	return 0;
}


