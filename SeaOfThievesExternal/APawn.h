#pragma once


#ifndef APAWN_H
#define APAWN_H

#include <Windows.h>

#include "drivercom.h"
#include "APlayerState.h"
#include "reversals.h"

class APawn {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

	APlayerState PlayerState;

public:


	APawn(){ }
	APawn(UINT_PTR p_address);


};



#endif // !APAWN_H
