#pragma once

#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <Windows.h>


#include "drivercom.h"


class AGameState {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;


public:

	AGameState();
	AGameState(UINT_PTR p_address);

	virtual bool isDeleted();
	virtual void update(UINT_PTR new_p_address);

};


#endif // !GAMESTATE_H
