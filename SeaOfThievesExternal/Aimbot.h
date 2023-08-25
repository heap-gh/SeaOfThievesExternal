#pragma once

#ifndef AIMBOT_H
#define AIMBOT_H

#include <Windows.h>
#include <iostream>

#include "UWorld.h"
#include "math.h"
#include "ProjectileWeapon.h"

enum Focus {

	NEAREST = 0,

};


struct AimbotSettings {

	bool on = false;
	float max_FOV = 0.0f;
	Focus focus_on = NEAREST;

};



class Aimbot {

private:

	AimbotSettings* settings = nullptr;

	UWorld* p_UWorld = nullptr;

	float rotationAmountX = 0.0f;
	float rotationAmountY = 0.0f;


public:

	Aimbot(){ }
	Aimbot(UWorld* p_UWorld, AimbotSettings* settings);

	void start();
	void setWorld(UWorld* ptr);

	AActor* getTarget();
	FRotation getTargetAngle(FVector target_vector);
	void setAngle(FRotation target_angle);
	void moveMouseBy(int deltaX, int deltaY);



};


#endif // !AIMBOT_H

