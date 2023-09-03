
#include "USceneComponent.h"


USceneComponent::USceneComponent(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

}


FVector USceneComponent::getCoords() {

	return FVector(this->d_address + Offsets::USceneComponent::Coords);

}


FVector USceneComponent::getVelocity() {

	return FVector(this->d_address + Offsets::USceneComponent::ComponentVelocity);
}