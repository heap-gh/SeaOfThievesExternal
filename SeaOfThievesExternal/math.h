#pragma once

#ifndef MATH_H
#define MATH_H

#include <Windows.h>

#include "drivercom.h"


class FRotation {


public:

	UINT_PTR b_address;

	float pitch, yaw, roll;

public:

	FRotation();
	FRotation(float pitch, float yaw, float roll);
	FRotation(UINT_PTR b_address);

	FRotation operator+ (FRotation vec) {
		return { pitch + vec.pitch, yaw + vec.yaw, roll + vec.roll };
	}



};



class FVector {

public:

	UINT_PTR b_address;

	float x, y, z;

public:

	FVector();
	FVector(float x, float y, float z);
	FVector(UINT_PTR b_address);

	FVector operator+ (FVector vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}


};


	

#endif // !MATH_H

