
#include "math.h"

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