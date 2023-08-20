#pragma once


#ifndef FGUID_H
#define FGUID_H

#include <Windows.h>

#include "drivercom.h"

class FGuid {

	INT32 A, B, C, D;

public:

	FGuid(){ }
	FGuid(UINT_PTR address);
	

	bool operator== (FGuid& fguid) {

		if (A == fguid.A && B == fguid.B && C == fguid.C && D == fguid.D)
			return true;

		return false;

	}

};






#endif // FGUID_H
