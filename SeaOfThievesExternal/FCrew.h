#pragma once

#ifndef FCREW_H
#define FCREW_H

#include "enums.h"
#include "includes.h"
#include "TArray.h"
#include "APlayerState.h"
#include "FGuid.h"

class FCrew {

public:

	UINT_PTR b_address;
	FString f_shipTemplate;
	FGuid CrewId;
	TArray<APlayerState> t_Players;

public:

	FCrew();
	FCrew(UINT_PTR b_address);

	ShipTemplate getShipTemplate();

};


#endif // !FCREW_H
