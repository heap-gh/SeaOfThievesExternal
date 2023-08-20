#pragma once


#ifndef USCENECOMPONENT_H
#define USCENECOMPONENT_H

#include <Windows.h>

#include "drivercom.h"
#include "math.h"
#include "reversals.h"

class USceneComponent {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;


public:

	USceneComponent() { }
	USceneComponent(UINT_PTR p_address);

	FVector getCoords();

};


#endif // !ROOTCOMPONENT_H
