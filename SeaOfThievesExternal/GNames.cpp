
#include "GNames.h"

UINT_PTR GNames::d_address = 0;

std::string GNames::getNameByID(UINT32 id) {

	UINT_PTR name_ptr = Driver::read<UINT_PTR>(GNames::d_address + (id / 0x4000) * 0x8);
	UINT_PTR name = Driver::read<UINT_PTR>(name_ptr + 0x8 * (id % 0x4000));

	return GNames::readString(name + 0x10);
}



std::string GNames::readString(UINT_PTR m_address) {

	int x = 0;

	std::string string = "";

	char letter = Driver::read<char>(m_address);

	while (letter != NULL) {
		x++;
		string += letter;
		letter = Driver::read<char>(m_address + x);
	}

	return string;
}