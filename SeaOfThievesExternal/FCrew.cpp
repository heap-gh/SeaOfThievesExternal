
#include "FCrew.h"


FCrew::FCrew(){ }


FCrew::FCrew(UINT_PTR b_address) {

	this->b_address = b_address;
	this->t_Players = TArray<APlayerState>(this->b_address + Offsets::FCrew::Players, 0x8);

	this->f_shipTemplate = FString(this->b_address + Offsets::FCrew::CrewSessionTemplate);

	this->CrewId = FGuid(this->b_address);
}


ShipTemplate FCrew::getShipTemplate() {

	std::string name = this->f_shipTemplate.get();

	if (name.find("Small") != std::string::npos)
		return SLOOP;

	if (name.find("Medium") != std::string::npos)
		return BRIGG;

	if (name.find("Large") != std::string::npos)
		return GALEON;

	return UNKNOWN;

}