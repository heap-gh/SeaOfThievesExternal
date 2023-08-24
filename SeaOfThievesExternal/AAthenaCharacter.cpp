
#include "AAthenaCharacter.h"

AAthenaCharacter::AAthenaCharacter() : AActor() { }


AAthenaCharacter::~AAthenaCharacter() {

	delete this->WieldedItemComponent;
}


AAthenaCharacter::AAthenaCharacter(UINT_PTR p_address) : AActor(p_address) {


	this->WieldedItemComponent = new UWieldedItemComponent(this->d_address + Offsets::AAthenaCharacter::WieldedItemComponent);

}


void AAthenaCharacter::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	AActor::update(this->p_address);

	
	if (this->WieldedItemComponent != nullptr) 
		this->WieldedItemComponent->update(this->d_address + Offsets::AAthenaCharacter::WieldedItemComponent);
	else 
		this->WieldedItemComponent = new UWieldedItemComponent(this->d_address + Offsets::AAthenaCharacter::WieldedItemComponent);
	
	
}