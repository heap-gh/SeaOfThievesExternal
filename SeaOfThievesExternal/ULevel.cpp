
#include "ULevel.h"

ULevel::ULevel(UINT_PTR p_address) {

	this->p_address = p_address;

	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->t_Actors = TArray<AActor>(this->d_address + Offsets::ULevel::Actors, 0x8);


}