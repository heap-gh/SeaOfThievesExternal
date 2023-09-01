
#include "math.h"

#define INACCURACY 0.5f

FVector::FVector() {

	this->b_address = 0;

	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;

}


FVector::FVector(float x, float y, float z) {

	this->b_address = 0;

	this->x = x;
	this->y = y;
	this->z = z;

}


FVector::FVector(UINT_PTR b_address) {

	this->b_address = b_address;

	this->x = Driver::read<float>(this->b_address);
	this->y = Driver::read<float>(this->b_address + 0x4);
	this->z = Driver::read<float>(this->b_address + 0x8);

}

float FVector::distance(FVector to) {

	return sqrtf(powf(to.x - this->x, 2) + powf(to.y - this->y, 2) + powf(to.z - this->z, 2));

}







FRotation::FRotation() {

	this->b_address = 0;

	this->pitch = 0.0f;
	this->yaw = 0.0f;
	this->roll = 0.0f;

}



FRotation::FRotation(float pitch, float yaw, float roll) {

	this->b_address = 0;

	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = roll;

}


FRotation::FRotation(UINT_PTR b_address) {

	this->b_address = b_address;

	this->pitch = Driver::read<float>(this->b_address);
	this->yaw = Driver::read<float>(this->b_address + 0x4);
	this->roll = Driver::read<float>(this->b_address + 0x8);

}


bool FRotation::about(float from, float to) {

	float diff = from - to;

	if (diff < INACCURACY && diff > -INACCURACY)
		return true;

	return false;

}


bool FRotation::about (FRotation rot){

	FRotation diff = rot - *this;

	if ((diff.pitch < INACCURACY && diff.pitch > -INACCURACY) && (diff.yaw < INACCURACY && diff.yaw > -INACCURACY))
		return true;

	return false;

}


float FRotation::shortestAngle(float fromAngle, float toAngle) {
	float angleDifference = toAngle - fromAngle;

	while (angleDifference < -180.0f)
		angleDifference += 360.0f;

	while (angleDifference > 180.0f)
		angleDifference -= 360.0f;

	return angleDifference;

}