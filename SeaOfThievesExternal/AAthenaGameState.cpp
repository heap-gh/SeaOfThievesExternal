
#include "AAthenaGameState.h"

AAthenaGameState::AAthenaGameState() {



}



AAthenaGameState::AAthenaGameState(UINT_PTR p_address){

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->p_ACrewService = new ACrewService(this->d_address + Offsets::AAthenaGameState::CrewService);
	if (p_ACrewService->t_Crews->size() < 30)
		this->initialized = true;

}


AAthenaGameState::~AAthenaGameState() {

	delete this->p_ACrewService;
}


bool AAthenaGameState::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}


void AAthenaGameState::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	if (this->p_ACrewService != nullptr) {
		this->p_ACrewService->update(this->d_address + Offsets::AAthenaGameState::CrewService);
		if (p_ACrewService->t_Crews->size() < 30)
			this->initialized = true;
		else
			this->initialized = false;
	}
	else {
		this->p_ACrewService = new ACrewService(this->d_address + Offsets::AAthenaGameState::CrewService);
		if (p_ACrewService->t_Crews->size() < 30)
			this->initialized = true;
		else
			this->initialized = false;
	}

}