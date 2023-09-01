
#include "APlayerCameraManager.h"



APlayerCameraManager::APlayerCameraManager(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);


}


FRotation APlayerCameraManager::getViewAngles() {

	return FRotation(this->d_address + Offsets::APlayerCameraManager::CameraCache);
}
