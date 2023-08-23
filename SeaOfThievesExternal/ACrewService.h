#pragma once

#ifndef ACREWSERVICE_H
#define ACREWSERVICE_H


#include "includes.h"
#include "FCrew.h"

class ACrewService {

public:

	UINT_PTR p_address;
	UINT_PTR d_address;

public:

	TArray<FCrew>* t_Crews = nullptr;

	ACrewService() { }
	ACrewService(UINT_PTR p_address);
	~ACrewService();

	void update(UINT_PTR new_p_address);

};


#endif // !ACREWSERVICE_H
