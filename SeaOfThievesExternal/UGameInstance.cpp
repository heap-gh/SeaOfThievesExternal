
#include "UGameInstance.h"



UGameInstance::UGameInstance(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->t_LocalPlayers = new TArray<ULocalPlayer>(this->d_address + Offsets::UGameInstance::LocalPlayers, 0x8);

}

UGameInstance::~UGameInstance() {

	delete this->t_LocalPlayers;
}


bool UGameInstance::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}


void UGameInstance::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	// Update TArray

}