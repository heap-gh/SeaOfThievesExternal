#pragma once

#ifndef AATHENAGAMESTATE_H
#define AATHENAGAMESTATE_H

#include "includes.h"
#include "ACrewService.h"


class AAthenaGameState  {

public:
	
	bool initialized = false;

	UINT_PTR p_address;
	UINT_PTR d_address;

	ACrewService* p_ACrewService = nullptr;


public:

	AAthenaGameState();
	AAthenaGameState(UINT_PTR p_address);
	~AAthenaGameState();

	
	bool isDeleted();
	void update(UINT_PTR new_p_address);

};


#endif // !AATHENAGAMESTATE_H
