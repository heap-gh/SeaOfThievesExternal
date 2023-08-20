
#include "FGuid.h"

FGuid::FGuid(UINT_PTR address) {

	this->A = Driver::read<INT32>(address);
	this->B = Driver::read<INT32>(address + 0x4);
	this->C = Driver::read<INT32>(address + 0x8);
	this->D = Driver::read<INT32>(address + 0xc);

}