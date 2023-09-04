
#include "Aimbot.h"

#define FLOATMAX  340282346638528859811704183484516925.f
#define PI		  3.1415926535897932385f
#define TO_DEG    57.295779513082f

Aimbot::Aimbot(UWorld* p_UWorld, AimbotSettings* settings) {

	setWorld(p_UWorld);
	this->settings = settings;

	this->m_angle_buffer = this->p_UWorld->p_address + 0x5F0; 
	this->m_access_switch = Driver::base_address + 0x26CFE0E;

}


void Aimbot::setWorld(UWorld* world) {

	this->p_UWorld = world;

}



void Aimbot::start() {

	while (!this->p_UWorld->initialized)
		Sleep(100);


	AActor*				target = nullptr;
	std::string			equipped_weapon_name = "";
	ProjectileWeapon*	equipped_weapon = nullptr;

	FVector				target_pos;
	FRotation			localangle;
	FRotation			target_angle;
	FRotation			anglediff;


	while (true) {


		while (this->settings->on) {

			equipped_weapon_name = this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName();
			equipped_weapon = (ProjectileWeapon*)this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem;

			while ((equipped_weapon_name.find("BP_wpn") != std::string::npos) && equipped_weapon->state() == AIMING) {
			
				equipped_weapon_name = this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName();
				target = getTarget();
				
				if (this->settings->fast_scope)
					int; // write 0x0 to in scope time
				else
					int; // write normal amount in scope time

				while (target != nullptr && equipped_weapon->state() == AIMING && !target->isDeleted()) {

					target_pos = target->RootComponent.getCoords();

					AimCorrection(
						this->p_UWorld->c_LocalActor->RootComponent.getVelocity(),
						target->RootComponent.getVelocity(),
						target_pos,
						this->p_UWorld->c_LocalActor->RootComponent.getCoords().distance(target_pos),
						equipped_weapon->getAmmoVelocity(),
						1.f);
					
					localangle = this->p_UWorld->c_LocalPlayer->PlayerController.PlayerCameraManager.getViewAngles();
					target_angle = getTargetAngle(target_pos);
					anglediff = getAngleDiff(localangle, target_angle);

					if ((std::abs(anglediff.yaw) <= this->settings->max_FOV) && (std::abs(anglediff.pitch) <= this->settings->max_FOV)) {
						
						if (this->settings->smooth_angle) 
							smoothAngle(localangle, target_angle, anglediff);
						else 
							writeAngleBuffer(target_angle);
						

						if (this->settings->auto_shoot)
							shootBullet();

					}
					 
				}

				disableAccess();

			}

		}

		Sleep(10);
	}

}


void Aimbot::smoothAngle(FRotation& current_angle, FRotation& target_angle, FRotation& angle_diff) {

	FRotation step = angle_diff / this->settings->smooth_amount;
	int max_count = static_cast<int>(this->settings->smooth_amount);

	for (int count = 0; count < max_count; count++) {
		current_angle.add(step);
		writeAngleBuffer(current_angle);
	}

	writeAngleBuffer(target_angle);

}


void Aimbot::shootBullet() {



}




AActor* Aimbot::getTarget() {

	AActor* target_actor = nullptr;

	if (this->settings->focus_on == NEAREST) {

		float target_distance = FLOATMAX;

		for (AActor& actor : this->p_UWorld->c_LocalCrew) {

			float distance = this->p_UWorld->c_LocalActor->RootComponent.getCoords().distance(actor.RootComponent.getCoords());
			
			if (distance < target_distance) {
				target_actor = &actor;
				target_distance = distance;
			}

		}

	}

	// more if checks for settings


	return target_actor;
}


void Aimbot::enableAccess() {

	if (this->m_access_switch == 0)
		return;

	if (!this->access) {
		Driver::write_memory(this->m_access_switch, (UINT_PTR)&*this->new_opcode, 0xB); // lea rdx, [SoTGame.exe + 859d350 + 5F0]
		this->access = true;
	}

}



void Aimbot::disableAccess() {

	if (this->m_access_switch == 0)
		return;

	if (this->access) {
		Driver::write_memory(this->m_access_switch, (UINT_PTR)&*this->old_opcode, 0xB); // xorps xmm1, xmm1
		this->access = false;
	}

}

FRotation Aimbot::getAngleDiff(FRotation& angle, FRotation& target_angle) {

	FRotation diff = target_angle - angle;

	if (diff.pitch > 180.0f) {
		diff.pitch -= 360.0f;
	}
	else if (diff.pitch < -180.0f) {
		diff.pitch += 360.0f;
	}

	if (diff.yaw > 180.0f) {
		diff.yaw -= 360.0f;
	}
	else if (diff.yaw < -180.0f) {
		diff.yaw += 360.0f;
	}


	return diff;
}


FRotation Aimbot::getTargetAngle(FVector& target_vector) {


		FVector delta = target_vector - this->p_UWorld->c_LocalActor->RootComponent.getCoords();
		delta.z -= 15.f;

		float yaw = atan2f(delta.y, delta.x) * (180.0f / PI);
		float pitch = atan2f(delta.z, sqrtf(powf(delta.x, 2) + powf(delta.y, 2))) * (180.0f / PI);

		if (yaw < 0.f) {
			yaw += 360.0f;
		}

		if (pitch < 0.f) {
			pitch += 360.0f;
		}

	return FRotation(pitch, yaw, 0.0f);

}



void Aimbot::AimCorrection(FVector local_velocity, FVector enemy_velocity, FVector& target_vector, float distance, float bullet_speed, float gravity) {

	target_vector = target_vector + enemy_velocity * (distance / fabs(bullet_speed));
	target_vector = target_vector - local_velocity * (distance / fabs(bullet_speed));
	float m_grav = fabs(gravity);
	float m_dist = distance / fabs(bullet_speed);
	target_vector.y += 0.5f * m_grav * m_dist * m_dist;

}


void Aimbot::writeAngleBuffer(FRotation& target_angle) {

	if (!isValidAngle(target_angle))
		return;

	Driver::write<float>(this->m_angle_buffer, target_angle.pitch);
	Driver::write<float>(this->m_angle_buffer + 0x4, target_angle.yaw);
	Driver::write<float>(this->m_angle_buffer + 0x8, target_angle.roll);

	enableAccess();



}

bool Aimbot::isValidAngle(FRotation& angle) {

	if (((angle.pitch > 0.0f && angle.pitch < 80.f) || (angle.pitch < 360.f && angle.pitch > 290.f)) && ((angle.yaw > 0.0f) && (angle.yaw < 360.0f)))
		return true;
		
	return false;
}

