
#include "AAthenaGameState.h"


AAthenaGameState::AAthenaGameState(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->p_ACrewService = ACrewService(this->d_address + Offsets::AAthenaGameState::CrewService);

}


bool AAthenaGameState::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}