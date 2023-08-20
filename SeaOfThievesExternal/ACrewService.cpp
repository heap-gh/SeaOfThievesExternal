
#include "ACrewService.h"


ACrewService::ACrewService(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->t_Crews = TArray<FCrew>(this->d_address + Offsets::ACrewService::Crews, 0x98);

}