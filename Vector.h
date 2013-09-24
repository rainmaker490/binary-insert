// Vector.h - template Vector class declaration
// Written by Varun Patel

#pragma once
#include<iostream>
#include<sstream>
#include<string>

using namespace std;

#define INITIAL_CAPACITY 20
#define CAPACITY_BOOST 10

template <typename DATA_TYPE>
class Vector
{
public:
	// Default/Init-constructor, creates a vector of the zero size
	// but the specified intialCapacity
	Vector(int initialCapacity = INITIAL_CAPACITY)
	{
		Size = 0;
		Capacity = initialCapacity;
		Data = new DATA_TYPE[initialCapacity];
	}

	// Copy constructor performs deep-copy [because there is a pointer as a data member]
	Vector(const Vector& source)
	{
		// To prevent assignment operator from crashing because initially
		// the Data pointer is set to some garbage value, yet
		// the = operator will attempt to delete it
		Data = NULL;
		*this = source;
	}

	// Destructor
	~Vector()
	{
		delete[] Data;
	}

	// Assignment operator, perform deep copy
	Vector& operator = (const Vector& source)
	{
		// Perform deep copy as follows:
		// 1. Disposes current Data
		delete [] Data;

		// 2. Allocates new Data
		Data = new DATA_TYPE[INITIAL_CAPACITY];

		// 3. Copies Size and Capacity
		Size = source.Size;
		Capacity = source.Capacity;

		// 4. Copies all array elements from source Data to this Data
		for (int i=0; i < Size; i++)
			(*this)[i] = source[i];

		// ALL assignment operators must return *this (reference
		// the current instance of the class)
		return *this;
	}

	// Check Bounds Function
	void CheckBounds(int index, const char* source) const
	{
		int length = Size;

		if ( ( index < 0) || (index >= length) )
		{
			std::stringstream error;
			error << " " << source << ": index" << index << " out of bounds (0..."  << (length - 1)<< ")";
			// Throwing a String
			throw std::string(error.str().c_str());
		}
	}

	// Returns an element of the Vector by reference so we could
	// modify it if needed; throws an exception when index is negative
	// or larger or equal to the Size
	DATA_TYPE& operator [] (int index) const
	{
		// Do bounds checking
		this->CheckBounds(index, "[] operator");
		return Data[index];
	}

	// Adds a new element to the Vector
	void Add(const DATA_TYPE& value)
	{
		Insert(value, Size);
	}

	// Inserts the value at the specified Index by moving the tail;
	// when Size = Capacity the Vector has to be reallocated first
	// to accomodate the new element
	void Insert(const DATA_TYPE& value, int index)
	{
		if (index > Size)
		{
			std::stringstream error;
			error <<" Vector Insert Function: Index: " << index << " out of bounds";
			throw error.str(); 
		}
		// If the capacity is not large enough then
		// allocate larger vector
		if ( Size >= Capacity)
		{
			// 0. Let's boost the capacity
			Capacity += CAPACITY_BOOST;

			// 1. Allocate new larger vector
			DATA_TYPE* newData = new DATA_TYPE[Capacity];

			// 2. Copy from old Data into newData
			for (int i=0; i < Size; i++)
				newData[i] = Data[i];

			// 3. Delete the old Data
			delete[] Data;

			// 4. Replace old Data-pointer with the newData pointer
			Data = newData;
		}

		// Move the tail
		for (int i = GetSize() - 1; i >= index; i--)
			Data[i + 1] = Data[i];
		
		// Insert
		Data[index] = value;
		Size++;

		
	}

	// Implementation of BinaryInsert Function
	// inserts a value in a sorted way
	void BinaryInsert(const DATA_TYPE& myValue, int startPos, int length)
	{
		// When the smallest subvector is found, determine if it's positions should be to the right or left
		// Insert first value at starting position when the vector is empty
		if ( length == 0)
		{
			Insert(myValue, startPos);
			return;
		}
		// When there is data in the vector, deermine the position it needs to be inserted to
		if ( length == 1 )
		{
			if (myValue > Data[startPos])
				Insert(myValue, startPos + 1);  // If Value is greater, Insert to the right
			else
				Insert(myValue, startPos);	  // If Value is lesser, Insert to the left
			return;
		}

		// Determine if the value of the middle element is larger than the value we are looking for
		if (Data[startPos + length/2] > myValue )
		// If the value of element is larger, recursively BinaryInsert the "first" half of the vector
			return BinaryInsert(myValue, startPos, length/2);
		else
		// If the value of element is not larger, recursively BinaryInsert the "second" half of the vector
			return BinaryInsert(myValue, startPos + length/2, length - length/2);
	}

	// myValue is put into vector in a sorted way through above function
	void BinaryInsert(const DATA_TYPE& myValue)
	{
		BinaryInsert(myValue, 0, Size);
	}

	// Removes an element from the Vector at the specified index
	// by moving the tail to the left
	void Remove(int index)
	{
		// Do bounds checking
		this->CheckBounds(index, "Remove Function");


		for (int i = index; i < Size - 1; i++)
			Data[i] = Data[i+1];
		Size--;
	}


	// Get accessors for Size and Capacity
	int GetSize() const
	{
		return Size;
	}

	int GetCapacity() const
	{
		return Capacity;
	}


private:
	// The encapsulated C- array given a pointer
	DATA_TYPE* Data;

	// Vector Size means how many elements in Data- array are actually used
	int Size;

	// Vector capacity means how many elements in Data- array are actually allocated
	int Capacity;
};

template<typename DATA_TYPE>
ostream& operator << (ostream& out, const Vector<DATA_TYPE>& aVector)
{
	// write a for-loop to output array elements
	for (int i = 0; i < aVector.GetSize(); i++)
	{
		out << aVector[i] << " ";
	}
	return out;
}
