#pragma once

#ifndef ACONTROLLER_H
#define ACONTROLLER_H

#include <Windows.h>

#include "math.h"
#include "reversals.h"

class AController {

public:
	
	UINT_PTR p_address;
	UINT_PTR d_address;

public:

	AController(){ }
	AController(UINT_PTR p_address);

	FRotation getViewAngles();


};



#endif // !ACONTROLLER_H
