#pragma once

#ifndef AActor_H
#define AActor_H


#include <string>
#include <Windows.h>


#include "drivercom.h"
#include "reversals.h"
#include "GNames.h"
#include "USceneComponent.h"
#include "APawn.h"

class AActor {

public:

	bool isInitialized = false;

	UINT_PTR p_address;
	UINT_PTR d_address;

	USceneComponent RootComponent;
	APawn Pawn;

public:

	AActor() { }
	AActor(UINT_PTR p_address);


	UINT32		getID();
	std::string getClassName();
	bool		isDeleted();


};


#endif // !AActor_H
