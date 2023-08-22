
#include "Aimbot.h"

Aimbot::Aimbot(UWorld* p_UWorld, AimbotSettings settings) {

	this->p_UWorld = p_UWorld;
	
	init(settings);

}


void Aimbot::setWorld(UWorld* world) {

	this->p_UWorld = world;
}



void Aimbot::init(AimbotSettings settings) {

	this->settings = settings;

	start();
}


void Aimbot::updateSettings(AimbotSettings settings) {

	this->settings = settings;
}


void Aimbot::start() {






}


AActor Aimbot::getTarget() {



	return AActor();
}

bool Aimbot::isScoped() {


	return false;
}