#pragma once


#ifndef UGAMEINSTANCE_H
#define UGAMEINSTANCE_H


#include <Windows.h>

#include "TArray.h"
#include "ULocalPlayer.h"
#include "reversals.h"

class UGameInstance {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

	TArray<ULocalPlayer>* t_LocalPlayers = nullptr;

public:

	UGameInstance(){ }
	UGameInstance(UINT_PTR p_address);
	~UGameInstance();

	bool isDeleted();
	void update(UINT_PTR new_p_address);

};



#endif // !UGAMEINSTANCE_H
