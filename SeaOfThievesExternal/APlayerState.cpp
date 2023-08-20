
#include "APlayerState.h"

APlayerState::APlayerState() { }


APlayerState::APlayerState(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->f_name = FString(this->d_address + Offsets::APlayerState::PlayerName);

	this->initialized = true;

}


std::string APlayerState::getName() {

	return this->f_name.get();
}


INT32 APlayerState::getId() {

	return Driver::read<INT32>(this->d_address + Offsets::APlayerState::PlayerId);
}