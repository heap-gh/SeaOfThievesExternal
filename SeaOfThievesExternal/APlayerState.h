#pragma once

#ifndef APLAYERSTATE_H
#define APLAYERSTATE_H

#include "FString.h"
#include "reversals.h"

class APlayerState {

public:

	bool initialized = false;

	UINT_PTR p_address;
	UINT_PTR d_address;

	FString f_name;

public:

	APlayerState();
	APlayerState(UINT_PTR p_address);

	std::string getName();
	INT32 getId();
	
};

#endif // !APLAYERSTATE_H
