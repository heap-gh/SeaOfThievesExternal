
#include "AActor.h"

AActor::AActor(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->RootComponent = USceneComponent(this->d_address + Offsets::AActor::RootComponent);

	this->Pawn = APawn(this->d_address + Offsets::AActor::Instigator);

	this->c_ActorID = Driver::read<UINT32>(this->d_address + Offsets::AActor::ActorID);

	this->isInitialized = true;
}


UINT32 AActor::getID() {

	return Driver::read<UINT32>(this->d_address + Offsets::AActor::ActorID);
}


std::string AActor::getClassName() {

	return GNames::getNameByID(this->getID());
}



bool AActor::isDeleted() {

	if (Driver::read<UINT_PTR>(this->p_address) != this->d_address) 
		return true;
	
	if (Driver::read<UINT32>(this->d_address + Offsets::AActor::ActorID) != this->c_ActorID)
		return true;

	return false;
}