
#include "Aimbot.h"

#define ANGLEMAX  79.f
#define ANGLEMIN -69.f
#define FLOATMAX  340282346638528859811704183484516925.f
#define PI		  3.1415926535897932385.f;
#define TO_DEG    57.295779513082f;

Aimbot::Aimbot(UWorld* p_UWorld, AimbotSettings* settings) {

	setWorld(p_UWorld);
	this->settings = settings;

}


void Aimbot::setWorld(UWorld* world) {

	this->p_UWorld = world;

}





void Aimbot::start() {

	while (!this->p_UWorld->initialized)
		Sleep(100);


	AActor* target = nullptr;
	std::string equipped_weapon_name = "";
	ProjectileWeapon* equipped_weapon = nullptr;

	while (true) {

		while (this->settings->on) {

			equipped_weapon_name = this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName();
			equipped_weapon = (ProjectileWeapon*)this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem;

			while ((equipped_weapon_name.find("BP_wpn") != std::string::npos) && equipped_weapon->state() == AIMING) {
			
				equipped_weapon_name = this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName();
				target = getTarget();

				//std::cout << "anglar\n";

				while (target != nullptr && equipped_weapon->state() == AIMING && !target->isDeleted()) {

					FRotation localangle = this->p_UWorld->c_LocalPlayer->PlayerController.PlayerCameraManager.getViewAngles();
					FRotation angle = getTargetAngle(target->RootComponent.getCoords());
					
					setAngle(angle);

					//std::cout << "ANGLE: " << angle.pitch << "  " << angle.yaw << " || " << localangle.pitch << "  " << localangle.yaw << "\n";

					//FVector coords = target->RootComponent.getCoords();
					//std::cout << target->Pawn.PlayerState.getName() << "  " << coords.x << " " << coords.y << " " << coords.z << "\n";
					
				}

			}

		}

		Sleep(100);
	}

}




FRotation Aimbot::getTargetAngle(FVector target_vector) {

	FVector delta = target_vector - this->p_UWorld->c_LocalActor->RootComponent.getCoords();

	float hyp = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

	float pitch = atan2f(delta.z, hyp) * TO_DEG;
	float yaw = atan2f(delta.y, delta.x) * TO_DEG;

	return { pitch, yaw, 0.0f };

}



void Aimbot::setAngle(FRotation target_angle) {

	if (target_angle.pitch < -69.f || target_angle.pitch > 79.f)
		return;

	FRotation current_angles = this->p_UWorld->c_LocalPlayer->PlayerController.PlayerCameraManager.getViewAngles();
	FRotation step;

	while (!current_angles.about(target_angle)) {

		current_angles = this->p_UWorld->c_LocalPlayer->PlayerController.PlayerCameraManager.getViewAngles();

		step = current_angles - target_angle;

		int rotYaw = 0.3f * step.yaw;
		int rotPitch = 0.3f * step.pitch; 

		if (rotYaw == 0) 
			rotYaw = step.yaw > 0.0f ? 1 : -1;
		
		if (rotPitch == 0)
			rotPitch = step.pitch > 0.0f ? 1 : -1;

		
		moveMouseBy(FRotation::about(current_angles.yaw, target_angle.yaw) ? 0 : rotYaw, FRotation::about(current_angles.pitch, target_angle.pitch) ? 0 : rotPitch);
		

		//moveMouseBy(rotYaw, rotPitch);

		
	}

	//std::cout << "DONE!\n";

}




AActor* Aimbot::getTarget() {

	AActor* target_actor = nullptr;

	if (this->settings->focus_on == NEAREST) {

		float target_distance = FLOATMAX;

		for (AActor& actor : this->p_UWorld->c_Enemies) {
			

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



void Aimbot::moveMouseBy(int deltaX, int deltaY) {
	
	INPUT input = {};
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = deltaX;
	input.mi.dy = deltaY;

	SendInput(1, &input, sizeof(INPUT));

}

