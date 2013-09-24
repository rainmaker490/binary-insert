// main.cpp - Binary Insert main entry point
// Written by Varun Patel

#include <iostream>
#include <string>
#include "Vector.h"

using namespace std;

#define DATA_SIZE 5

void main()
{
	string myString;
	Vector<string> myVector;

	// Ask User to input myString
	cout << "Enter " << DATA_SIZE << " strings that you would like to be sorted alphabetically: " << endl;
	cout << endl;

	for (int i = 0; i < DATA_SIZE; i++)
	{
		// Capture user input string into myString using for-loop
		cin >> myString;
		// BinaryInsert function is implemented in Vector class [see header file]
		// Vector Class from previous Vector Lab used
		myVector.BinaryInsert(myString);
	}
	cout << endl;

	// Print Result
	cout << "Here are your alphabetically sorted strings:" << endl;
	cout << endl;
	cout << myVector << endl;

	cout << endl;
	system("pause");
}