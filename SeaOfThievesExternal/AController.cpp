
#include "AController.h"


AController::AController(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

}



FRotation AController::getViewAngles() {

	return FRotation(this->d_address + Offsets::AController::ControlRotation);
}