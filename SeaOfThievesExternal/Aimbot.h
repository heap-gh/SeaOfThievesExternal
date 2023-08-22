#pragma once

#ifndef AIMBOT_H
#define AIMBOT_H

#include <Windows.h>

#include "UWorld.h"
#include "math.h"

enum Focus {

	NEAREST = 0,

};


struct AimbotSettings {

	float max_FOV = 0.0f;
	Focus focus_on = NEAREST;

};



class Aimbot {

private:

	AimbotSettings settings;

	UWorld* p_UWorld = nullptr;


public:

	Aimbot(){ }
	Aimbot(UWorld* p_UWorld, AimbotSettings settings);

	void init(AimbotSettings settings);
	void start();
	void updateSettings(AimbotSettings settings);
	void setWorld(UWorld* ptr);

	AActor getTarget();
	bool isScoped();

};


#endif // !AIMBOT_H

