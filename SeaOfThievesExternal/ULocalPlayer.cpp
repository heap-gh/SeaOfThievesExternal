
#include "ULocalPlayer.h"

ULocalPlayer::ULocalPlayer(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->PlayerController = APlayerController(this->d_address + Offsets::ULocalPlayer::PlayerController);

}





void ULocalPlayer::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->PlayerController = APlayerController(this->d_address + Offsets::ULocalPlayer::PlayerController);

}