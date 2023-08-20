#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "includes.h"
#include "ACrewService.h"

class AAthenaGameState {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;
	
	ACrewService p_ACrewService;


public:

	AAthenaGameState() {  }
	AAthenaGameState(UINT_PTR p_address);
	
	bool isDeleted();

};


#endif // !GAMESTATE_H
