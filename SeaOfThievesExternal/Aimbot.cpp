
#include "Aimbot.h"

Aimbot::Aimbot(UWorld* p_UWorld, AimbotSettings* settings) {

	setWorld(p_UWorld);
	this->settings = settings;

}


void Aimbot::setWorld(UWorld* world) {

	this->p_UWorld = world;

}





void Aimbot::start() {










}


AActor Aimbot::getTarget() {



	return AActor();
}

bool Aimbot::isScoped() {


	return false;
}