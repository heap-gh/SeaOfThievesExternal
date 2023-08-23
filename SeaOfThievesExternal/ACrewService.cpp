
#include "ACrewService.h"


ACrewService::ACrewService(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	this->t_Crews = new TArray<FCrew>(this->d_address + Offsets::ACrewService::Crews, 0x98);

}


ACrewService::~ACrewService() {

	delete this->t_Crews;
}


void ACrewService::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	if (this->t_Crews != nullptr) {
		this->t_Crews->update(this->d_address + Offsets::ACrewService::Crews);
	}
	else {
		new TArray<FCrew>(this->d_address + Offsets::ACrewService::Crews, 0x98);
	}


}