#pragma once


#ifndef FSTRING_H
#define FSTRING_H

#include <Windows.h>
#include <string>

#include "drivercom.h"

class FString {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

public:

	FString() { };
	FString(UINT_PTR p_address);

	UINT32 size();
	std::string get();

};


#endif // !FSTRING_H
