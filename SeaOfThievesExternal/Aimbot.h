#pragma once

#ifndef AIMBOT_H
#define AIMBOT_H

#include <Windows.h>

#include "UWorld.h"
#include "math.h"

class Aimbot {

public:	

	UWorld* p_UWorld = nullptr;


public:

	Aimbot(){ }
	Aimbot(UWorld* p_UWorld);

};


#endif // !AIMBOT_H

