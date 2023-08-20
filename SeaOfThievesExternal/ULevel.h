#pragma once

#ifndef ULEVEL_H
#define ULEVEL_H


#include <Windows.h>

#include "drivercom.h"
#include "TArray.h"
#include "AActor.h"
#include "reversals.h"

class ULevel {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

	TArray<AActor> t_Actors;

public:

	ULevel(){ }
	ULevel(UINT_PTR p_address);
	


};


#endif // !ULEVEL_H
