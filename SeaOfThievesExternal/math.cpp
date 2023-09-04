
#include "math.h"

FVector::FVector() {

	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;

}


FVector::FVector(float x, float y, float z) {

	this->x = x;
	this->y = y;
	this->z = z;

}


float FVector::distance(FVector to) {

	return sqrtf(powf(to.x - this->x, 2) + powf(to.y - this->y, 2) + powf(to.z - this->z, 2));

}




FRotation::FRotation() {

	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

}



FRotation::FRotation(float pitch, float yaw, float roll) {

	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

}


void FRotation::add(FRotation& amount) {

	this->pitch += amount.pitch;

	if (this->pitch > 360.f)
		this->pitch -= 360.f;

	if (this->pitch < 0.0f)
		this->pitch += 360.f;

	this->yaw += amount.yaw;

	if (this->yaw > 360.f)
		this->yaw -= 360.f;

	if (this->yaw < 0.0f)
		this->yaw += 360.f;

}

