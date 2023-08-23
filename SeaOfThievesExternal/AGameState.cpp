
#include "AGameState.h"


AGameState::AGameState() {


}

AGameState::AGameState(UINT_PTR p_address) {
	
	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

}



bool AGameState::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}


void AGameState::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

}