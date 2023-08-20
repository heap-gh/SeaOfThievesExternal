
#include "UGameInstance.h"



UGameInstance::UGameInstance(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->t_LocalPlayers = TArray<ULocalPlayer>(this->d_address + Offsets::UGameInstance::LocalPlayers, 0x8);

}


bool UGameInstance::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}