
#include "APawn.h"



APawn::APawn(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->PlayerState = APlayerState(this->d_address + Offsets::APawn::PlayerState);
	this->Controller = AController(this->d_address + Offsets::APawn::Controller);

}