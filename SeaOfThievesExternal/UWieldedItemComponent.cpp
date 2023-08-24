
#include "UWieldedItemComponent.h"

UWieldedItemComponent::UWieldedItemComponent() {


}


UWieldedItemComponent::~UWieldedItemComponent() {

	delete this->CurrentlyWieldedItem;
}


UWieldedItemComponent::UWieldedItemComponent(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->CurrentlyWieldedItem = new AActor(this->d_address + Offsets::UWieldedItemComponent::CurrentlyWieldedItem);

}

void UWieldedItemComponent::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	if (this->CurrentlyWieldedItem != nullptr)
		this->CurrentlyWieldedItem->update(this->d_address + Offsets::UWieldedItemComponent::CurrentlyWieldedItem);
	else
		this->CurrentlyWieldedItem = new AActor(this->d_address + Offsets::UWieldedItemComponent::CurrentlyWieldedItem);
	
}
