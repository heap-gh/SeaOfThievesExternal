#pragma once

#ifndef APLAYERCAMERAMANAGER_H
#define APLAYERCAMERAMANAGER_H


#include <Windows.h>

#include "drivercom.h"
#include "math.h"
#include "reversals.h"

class APlayerCameraManager {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;


public:	

	APlayerCameraManager(){ }
	APlayerCameraManager(UINT_PTR p_address);

	FRotation getViewAngles();

};


#endif // !APLAYERCAMERAMANAGER_H

