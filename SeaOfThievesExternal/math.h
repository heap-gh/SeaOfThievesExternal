#pragma once

#ifndef MATH_H
#define MATH_H

#include <Windows.h>

#include "drivercom.h"


class FRotation {


public:

	UINT_PTR b_address;

	float pitch, yaw;
	float roll = 0.0f;

public:

	FRotation();
	FRotation(float pitch, float yaw, float roll);
	FRotation(UINT_PTR b_address);

	bool about(FRotation rot);
	static bool about(float from, float to);

	FRotation operator+= (FRotation vec) {
		return { pitch += vec.pitch, yaw += vec.yaw, roll += vec.roll };
	}

	FRotation operator- (FRotation vec) {
				
		return { pitch - vec.pitch, yaw - vec.yaw, roll - vec.roll };
	}

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

	float distance(FVector to);

	FVector operator* (float f) {
		return { x * f, y * f, z * f };
	}

	FVector operator* (FVector vec) {
		return { x * vec.x, y * vec.y, z * vec.z };
	}

	FVector operator+ (FVector vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}

	FVector operator+= (FVector vec) {
		return { x += vec.x, y += vec.y, z += vec.z };
	}

	FVector operator- (FVector vec) {
		return { x - vec.x, y - vec.y, z - vec.z };
	}
	


};


	

#endif // !MATH_H

