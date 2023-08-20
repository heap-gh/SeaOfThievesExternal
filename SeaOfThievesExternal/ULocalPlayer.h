#pragma once

#ifndef ULOCALPLAYER_H
#define ULOCALPLAYER_H

#include <Windows.h>

#include "drivercom.h"
#include "APlayerController.h"
#include "FGuid.h"

class ULocalPlayer {


public:

	UINT_PTR p_address;
	UINT_PTR d_address;

	APlayerController PlayerController;


public:

	ULocalPlayer() { }
	ULocalPlayer(UINT_PTR p_address);



};

#endif // !ULOCALPLAYER_H
