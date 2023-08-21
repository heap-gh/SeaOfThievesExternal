#pragma once


#ifndef TARRAY_H
#define TARRAY_H

#include <Windows.h>
#include <vector>
#include <string>

#include "drivercom.h"

template <class T>
class TArray {

	/*
	* 
	* 0x0 pointer to array
	* 0xA size
	* 0xC max size
	*
	*/


public:

	UINT_PTR d_dataptr; // pointer that is pointing at the element or the pointer in the T-array pointer list
	unsigned int data_size; // size of the structure or pointer in the array
	std::vector<T> data = { };
	
public:

	UINT_PTR address; //the address of the pointer to d_dataptr
	

public:

	TArray(){ }
	TArray(UINT_PTR address, int size) {

		this->address = address;
		
		this->d_dataptr = Driver::read<UINT_PTR>(this->address);

		this->data_size = size;
		
		update();

	}



	T at(int idx) {
		
		T t;

		try {
			t = this->data.at(idx);
		}
		catch (std::out_of_range e) { }
		

		return t;

	}


	int size() {

		return Driver::read<INT32>(this->address + 0x8);
	}


	int max_size() {

		return Driver::read<INT32>(this->address + 0xC);
	}

	T* operator[](int idx) {

		return at(idx);
	}
	
	void update() {

		this->data.clear();

			for (int x = 0; x < size(); x++) {
				this->data.push_back(T(this->d_dataptr + x * this->data_size));
			}
		

	}

	static bool contains(T& object) {

		for (T& data_object : this->data) {
			if (data_object.d_address == object.d_address) {
				return true;
			}
		}

		return false;
	}

	bool isDeleted() {

		if (Driver::read<UINT_PTR>(this->address) != this->d_dataptr)
			return true;

		return false;

	}



};



#endif // !TARRAY_H
