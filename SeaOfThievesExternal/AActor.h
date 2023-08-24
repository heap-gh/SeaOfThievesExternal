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

	UINT_PTR p_address;
	UINT_PTR d_address;

	USceneComponent RootComponent;
	APawn Pawn;

public:

	AActor() { }
	AActor(UINT_PTR p_address);
	


	UINT32 c_ActorID = 0;


	UINT32		getID();
	std::string getClassName();
	bool		isDeleted();
	void		update(UINT_PTR new_p_address);

};


#endif // !AActor_H
