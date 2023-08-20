
#include "FString.h"


FString::FString(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

}


UINT32 FString::size() {

 	return Driver::read<UINT32>(this->p_address + 0x8);
}


std::string FString::get() {

	std::string string = "";
	UINT32 name_size = size();

	if (name_size != 0) {

		for (unsigned int x = 0; x < name_size * 2 - 2; x++) {

			if (x % 2 == 0)
				string += Driver::read<char>(this->d_address + x);

		}

	}

	return string;
}


