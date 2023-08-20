
#include "APlayerController.h"

APlayerController::APlayerController(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->PlayerCameraManager = APlayerCameraManager(this->d_address + Offsets::APlayerController::CameraManager);

	this->Pawn = APawn(this->d_address + Offsets::APlayerController::Pawn);

}