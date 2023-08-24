#pragma once


#ifndef UWIELDEDITEMCOMPONENT_H
#define UWIELDEDITEMCOMPONENT_H

#include <Windows.h>

#include "drivercom.h"
#include "AActor.h"

class UWieldedItemComponent {

public:	


	UINT_PTR p_address;
	UINT_PTR d_address;

	AActor* CurrentlyWieldedItem;


public:

	UWieldedItemComponent();
	UWieldedItemComponent(UINT_PTR p_address);
	~UWieldedItemComponent();

	void update(UINT_PTR new_p_address);

};



#endif // !UWIELDEDITEMCOMPONENT_H
