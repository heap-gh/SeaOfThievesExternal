
#include "client.h"


Client::Client() {

	init();

}


Client::~Client() {




}


void Client::init() {
	
	Driver::process_id = Driver::get_process_id("SoTGame.exe");
	Driver::base_address = Driver::get_module_base_address("SoTGame.exe");
	
	if (Driver::base_address == NULL)
		exit(0);
	
	GNames::d_address = Driver::read<UINT_PTR>(Driver::base_address + Offsets::Process::GNames);

	this->p_UWorld = new UWorld(Driver::base_address + Offsets::Process::UWorld);
	this->aimbot = new Aimbot(this->p_UWorld);
		
	std::cout << "GNAMES ADDR: " << std::hex << GNames::d_address << "\n";
	std::cout << "PROCID: " << Driver::process_id << "\nBASEADDR: " << std::hex << Driver::base_address << "\n";
	std::cout << "UWORLD ADDR: " << p_UWorld->p_address << "\n";
	std::cout << "AATHENAGAMESTATE ADDR: " << p_UWorld->p_AAthenaGameState->p_address << "\n";
	std::cout << "ACREWSERVICE ADDR: " << p_UWorld->p_AAthenaGameState->p_ACrewService.p_address << "\n";
	std::cout << "CREWS ADDR: " << p_UWorld->p_AAthenaGameState->p_ACrewService.t_Crews.address << "\n";
	std::cout << "CREWS SIZE: " << p_UWorld->p_AAthenaGameState->p_ACrewService.t_Crews.size() << "\n";
	std::cout << "LEVLES ADDR: " << p_UWorld->t_Levels.address << "\n";
	std::cout << "FIRST ACTOR ADDR: " << p_UWorld->t_Levels.at(0).t_Actors.at(0).p_address << "\n";

	FCrew p = p_UWorld->p_AAthenaGameState->p_ACrewService.t_Crews.at(0);
	//std::cout << "XD: " << p.b_address << "\n";
	std::cout << "SIZE: " << p.t_Players.size() << "\n";
	std::cout << "NAME: " << p.t_Players.at(0).getName() << "\n";
	std::cout << "ADDR: " << p.t_Players.at(0).p_address << "\n";
	std::cout << "ID: " << std::dec << p.t_Players.at(0).getId() << "\n";
	std::cout << p.getShipTemplate() << "\n";

	//test

	/*

	for (int x = 0; x < p_UWorld->t_Levels.size(); x++) {
		for (int y = 0; y < p_UWorld->t_Levels.at(x).t_Actors.size(); y++) {
			if (p_UWorld->t_Levels.at(x).t_Actors.at(y).getName() == "BP_PlayerPirate_C") {
				std::cout << std::hex << p_UWorld->t_Levels.at(x).t_Actors.at(y).d_address << "\n";
				
				AActor actor = p_UWorld->t_Levels.at(x).t_Actors.at(y);

				while (true) {
					std::cout << std::hex << actor.p_address << "  ";
					FVector ad = actor.RootComponent.getCoords();
					std::cout << ad.x << "  " << ad.y << "  " << ad.z << "\n";
					Sleep(50);
				}
			}
		}
		
	}

	*/

	FRotation f = this->p_UWorld->p_UGameInstance->t_LocalPlayers.at(0).PlayerController.PlayerCameraManager.getViewAngles();
	std::cout << "LOCALPLAYERNAME :" << this->p_UWorld->p_UGameInstance->t_LocalPlayers.at(0).PlayerController.Pawn.PlayerState.getName() << "\n";
	std::cout << "VIEWANGLES: " << f.pitch << "  " << f.yaw << "  " << f.roll << "\n";

	start();

}




void Client::start() {

	std::thread caching_thread(&Client::caching, this);

	bool show = false;
	while (true) {

		if (!show)
			std::cout << std::hex <<this->p_UWorld->d_address << "    " << this->p_UWorld->t_Levels.d_dataptr << "\n";
		
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
			show = !show;

		if (show) {

			AActor* localplayer = &this->p_UWorld->c_LocalPlayer;

			std::cout << "(" << this->p_UWorld->c_BP_PlayerPirate_C.size() << ")  ";

			for (AActor& ac : this->p_UWorld->c_BP_PlayerPirate_C) {
				std::cout << ac.Pawn.PlayerState.getName() << "    ";
			}
			std::cout << "  ||  ";

			for (AActor& ac : this->p_UWorld->c_LocalCrew) {
				std::cout << ac.Pawn.PlayerState.getName() << "    ";
			}

			std::cout << "  ||  ";

			for (AActor& ac : this->p_UWorld->c_Enemies) {
				std::cout << ac.Pawn.PlayerState.getName() << "    ";
			}


			std::cout << "\n";

		}
	}


	if(caching_thread.joinable())
		caching_thread.join();

}


void Client::caching() {

	
	std::thread fastCacher(&Client::fastCache, this);
	std::thread slowCacher(&Client::slowCache, this);
	std::thread extremeSlowCacher(&Client::extremeSlowCache, this);


	fastCacher.join();
	slowCacher.join();
	extremeSlowCacher.join();
}


void Client::fastCache() {

	while (true) {

		this->fastCache_lock.lock();

		this->p_UWorld->updateEnemies();

		this->fastCache_lock.unlock();

		Sleep(50);

		
	}

	
}



void Client::slowCache() {

	while (true) {

		this->slowCache_lock.lock();

		this->p_UWorld->updateActors();
		this->p_UWorld->updateLocalPlayer();
		this->p_UWorld->updateLocalCrew();

		this->slowCache_lock.unlock();

	}
}



void Client::extremeSlowCache() {

	while (true) {

		update();
		this->p_UWorld->updateWorld();
		this->p_UWorld->updateCrewId();
		this->p_UWorld->p_AAthenaGameState->p_ACrewService.t_Crews.update();

		Sleep(1000);

		
		
	}

}


void Client::update() {

	if (this->p_UWorld->isDeleted()) {

		this->fastCache_lock.lock();
		this->slowCache_lock.lock();

		delete this->p_UWorld;
		this->p_UWorld = new UWorld(Driver::base_address + Offsets::Process::UWorld);
		this->aimbot->p_UWorld = this->p_UWorld;
		
		this->fastCache_lock.unlock();
		this->slowCache_lock.unlock();
		

	}

}


void someRandomFunction() {


	// test

}