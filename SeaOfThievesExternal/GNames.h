#pragma once

#ifndef GNAMES_H
#define GNAME_H

#include <string>

#include "drivercom.h"
#include "reversals.h"

class GNames {

public:

	static UINT_PTR d_address;

	static std::string getNameByID(UINT32 id);
	static std::string readString(UINT_PTR m_address);


};


#endif // !GNAMES_H
