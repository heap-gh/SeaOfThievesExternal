#pragma once

#ifndef MATH_H
#define MATH_H

#include <Windows.h>

#include "drivercom.h"


class FRotation {


public:

	float pitch, yaw, roll;

public:

	FRotation();
	FRotation(float pitch, float yaw, float roll);


	void add(FRotation& amount);

	FRotation operator+= (FRotation vec) {
		return { pitch += vec.pitch, yaw += vec.yaw, roll += vec.roll };
	}

	FRotation operator- (FRotation vec) {
				
		return { pitch - vec.pitch, yaw - vec.yaw, roll - vec.roll };
	}

	FRotation operator+ (FRotation vec) {
		return { pitch + vec.pitch, yaw + vec.yaw, roll + vec.roll };
	}

	FRotation operator/ (float f) {
		return { pitch / f, yaw / f, roll / f };
	}



};



class FVector {

public:

	float x, y, z;

public:

	FVector();
	FVector(float x, float y, float z);

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

