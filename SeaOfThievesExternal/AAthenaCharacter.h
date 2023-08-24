#pragma once


#ifndef AATHENACHARACTER_H
#define AATHENACHARACTER_H

#include "AActor.h"
#include "UWieldedItemComponent.h"

class AAthenaCharacter : public AActor {

public:

	UWieldedItemComponent* WieldedItemComponent = nullptr;


public:

	AAthenaCharacter();
	AAthenaCharacter(UINT_PTR p_address); 
	~AAthenaCharacter();

	void update(UINT_PTR new_p_address);

};



#endif // !AATHENACHARACTER_H
