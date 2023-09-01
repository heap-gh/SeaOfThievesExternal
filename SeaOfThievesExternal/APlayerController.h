#pragma once


#ifndef APLAYERCONTROLLER_H
#define APLAYERCONTROLLER_H

#include <Windows.h>

#include "drivercom.h"
#include "APlayerCameraManager.h"
#include "reversals.h"
#include "APawn.h"

class APlayerController {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

	APlayerCameraManager PlayerCameraManager;
	APawn Pawn;


public:


	APlayerController() { }
	APlayerController(UINT_PTR p_address);


};


#endif // !APLAYERCONTROLLER_H
