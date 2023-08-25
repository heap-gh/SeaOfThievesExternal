#pragma once

#ifndef ENUMS_H
#define ENUMS_H


enum ShipTemplate {

	UNKNOWN = -1,
	SLOOP = 0,
	BRIGG = 1,
	GALEON = 2

};



enum EProjectileWeaponState
{

	EQUIPPING = 0,
	IDLE = 1,
	AIMING = 2,
	RECOIL = 3,
	RELOADING = 4,
	INTERRUPTEDRELOAD = 5,
	EXPROJECTILEWEAPONSTATE_MAX = 6,

};


#endif // !ENUMS_H