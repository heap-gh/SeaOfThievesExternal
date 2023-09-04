
#include "ProjectileWeapon.h"


ProjectileWeapon::ProjectileWeapon() : AActor() {


}


ProjectileWeapon::ProjectileWeapon(UINT_PTR p_address) : AActor(p_address) {

	

}


EProjectileWeaponState ProjectileWeapon::state() {

	return Driver::read<EProjectileWeaponState>(this->d_address + Offsets::AProjectileWeapon::State);

}


float ProjectileWeapon::getAmmoVelocity() {
			
	return Driver::read<float>(this->d_address + Offsets::AProjectileWeapon::Velocity);
}


void ProjectileWeapon::setIntoAimingDuration(INT32 duration) {

	Driver::write<INT32>(this->d_address + Offsets::AProjectileWeapon::IntoAimingDuration, duration);
}