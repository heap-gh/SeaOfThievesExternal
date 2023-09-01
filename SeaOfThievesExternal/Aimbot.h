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

	bool access = false;

	UINT_PTR m_angle_buffer = 0;
	UINT_PTR m_access_switch = 0;

	const char* new_opcode = "\x48\x8D\x15\xCB\x7B\xFB\x05\x90\x90\x90\x90";
	const char* old_opcode = "\x0F\x57\xC9\xF3\x0F\x10\x91\xFC\x03\x00\x00";

public:

	Aimbot(){ }
	Aimbot(UWorld* p_UWorld, AimbotSettings* settings);

	void start();
	void setWorld(UWorld* ptr);


	void enableAccess();
	void disableAccess();
	AActor* getTarget();
	FRotation getTargetAngle(FVector& target_vector);
	void writeAngleBuffer(FRotation& target_angle);
	bool isValidAngle(FRotation& angle);
	FRotation getAngleDiff(FRotation& angle, FRotation& target_angle);

};


#endif // !AIMBOT_H

