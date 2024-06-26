#pragma once


#ifndef PROJECTILEWEAPON_H
#define PROJECTILEWEAPON_H

#include "AActor.h"
#include "enums.h"



class ProjectileWeapon : public AActor {

public:

	ProjectileWeapon();
	ProjectileWeapon(UINT_PTR p_address);

	EProjectileWeaponState state();

	float getAmmoVelocity();
	void setIntoAimingDuration(INT32 duration);


};


#endif // !PROJECTILEWEAPON_H
