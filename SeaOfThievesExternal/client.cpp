
#include "client.h"


Client::Client() {

	init();

}


Client::~Client() {




}


void Client::init() {
	
	Driver::process_id = Driver::get_process_id("SoTGame.exe");
	
	if (Driver::process_id == NULL)
		exit(0);
	
	Driver::base_address = Driver::get_module_base_address("SoTGame.exe");
	
	if (Driver::base_address == NULL)
		exit(0);
	
	GNames::d_address = Driver::read<UINT_PTR>(Driver::base_address + Offsets::Process::GNames);

	this->p_UWorld = new UWorld(Driver::base_address + Offsets::Process::UWorld);
	
	AimbotSettings settings;

	this->p_Aimbot = new Aimbot(this->p_UWorld, settings);
		
	std::cout << "GNAMES ADDR: " << std::hex << GNames::d_address << "\n";
	std::cout << "PROCID: " << Driver::process_id << "\nBASEADDR: " << std::hex << Driver::base_address << "\n";
	std::cout << "UWORLD ADDR: " << p_UWorld->p_address << "\n";
	std::cout << "AATHENAGAMESTATE ADDR: " << p_UWorld->p_AAthenaGameState->p_address << "\n";
	std::cout << "ACREWSERVICE ADDR: " << p_UWorld->p_AAthenaGameState->p_ACrewService->p_address << "\n";
	std::cout << "CREWS ADDR: " << p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->address << "\n";
	std::cout << "CREWS SIZE: " << p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->size() << "\n";
	std::cout << "LEVLES ADDR: " << p_UWorld->t_Levels->address << "\n";
	std::cout << "FIRST ACTOR ADDR: " << p_UWorld->t_Levels->at(0).t_Actors.at(0).p_address << "\n";

	FCrew p = p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(0);
	//std::cout << "XD: " << p.b_address << "\n";
	std::cout << "SIZE: " << p.t_Players.size() << "\n";
	std::cout << "NAME: " << p.t_Players.at(0).getName() << "\n";
	std::cout << "ADDR: " << p.t_Players.at(0).p_address << "\n";
	std::cout << "ID: " << std::dec << p.t_Players.at(0).getId() << "\n";
	std::cout << p.getShipTemplate() << "\n";


	FRotation f = this->p_UWorld->p_UGameInstance->t_LocalPlayers->at(0).PlayerController.PlayerCameraManager.getViewAngles();
	std::cout << "LOCALPLAYERNAME :" << this->p_UWorld->p_UGameInstance->t_LocalPlayers->at(0).PlayerController.Pawn.PlayerState.getName() << "\n";
	std::cout << "VIEWANGLES: " << f.pitch << "  " << f.yaw << "  " << f.roll << "\n";

	//testing();
	start();

}


void Client::initLocalPlayer() {

	// Init local player first
	while (this->p_UWorld->c_LocalActor == nullptr) {
		update();
		updateActors();
		updateLocalPlayer();
	}
}


// testing threads
void Client::testing() {
	
	while (true) {
		update();
		updateActors();
		updateLocalPlayer();

		for (AActor& actor : this->p_UWorld->c_BP_PlayerPirate_C) {
			std::cout << actor.Pawn.PlayerState.getName() << "  " << std::hex << actor.p_address << " | ";
		}

		this->p_UWorld->c_BP_PlayerPirate_C.clear();
		std::cout << " ||  ";
		if (this->p_UWorld->c_LocalActor != nullptr)
			std::cout << "LOCAL: " << this->p_UWorld->c_LocalActor->p_address << "  " << this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName() << "  " << this->p_UWorld->p_UGameInstance->t_LocalPlayers->at(0).PlayerController.Pawn.PlayerState.getName() << "\n";

		std::cout << "\n";

	}

}


void Client::start() {

	initLocalPlayer();

	std::thread caching_thread(&Client::caching, this);

	bool show = false;
	bool showThreads = false;
	while (true) {

		

		if (!show) {

			FVector coords = this->p_UWorld->c_LocalActor->RootComponent.getCoords();

			std::cout << "\rBP_Pirate: " << this->p_UWorld->c_BP_PlayerPirate_C.size()
				<< " | LocalCrew: " << this->p_UWorld->c_LocalCrew.size()
				//<< " | Enemies: " << this->p_UWorld->c_Enemies.size()
				<< " | LocalAddr: " << std::hex << this->p_UWorld->c_LocalActor->p_address
				<< " | Wield: " << std::hex << this->p_UWorld->c_LocalActor->WieldedItemComponent->CurrentlyWieldedItem->getClassName()
				<< " | t_Levels: " << this->p_UWorld->t_Levels->data.size()
				//<< " | t_localPlayers: " << this->p_UWorld->p_UGameInstance->t_LocalPlayers->data.size()
				//<< " | t_Crews: " << this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->data.size()
				<< " | COORDS: " << coords.x << "  " << coords.y << "  " << coords.z
				<< std::flush;
			

		}
			
		
		if (GetAsyncKeyState(VK_NUMPAD1) & 1)
			show = !show;

		if (show) {

			std::cout << this->p_UWorld->c_LocalActor->d_address << " || ";

			std::cout << "(" << this->p_UWorld->c_BP_PlayerPirate_C.size() << ")  ";

			for (AActor& ac : this->p_UWorld->c_BP_PlayerPirate_C) {
				std::cout << ac.Pawn.PlayerState.getName() << "    " << ac.p_address << "    ";
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
		
		Sleep(55);
	}


	if(caching_thread.joinable())
		caching_thread.join();

}


void Client::caching() {

	std::thread fastCacher(&Client::fastCache, this);
	std::thread slowCacher(&Client::slowCache, this);
	std::thread extremeSlowCacher(&Client::extremeSlowCache, this);
	std::thread worldCacher(&Client::worldCache, this);


	worldCacher.join();
	fastCacher.join();
	slowCacher.join();
	extremeSlowCacher.join();
}


void Client::fastCache() {

	while (true) {

		this->fastCache_lock.lock();

		this->updateEnemies();
		this->updateLocalPlayer();

		this->fastCache_lock.unlock();
		
		Sleep(50);

	}


}



void Client::worldCache() {

	while (true) {

		this->update();

		Sleep(1000);
	}

}


void Client::slowCache() {

	while (true) {

		this->slowCache_lock.lock();

		this->updateActors();
		this->updateLocalCrew();

		this->slowCache_lock.unlock();
	
		Sleep(100);
	}


}



void Client::extremeSlowCache() {

	while (true) {

		this->extremeSlowCache_lock.lock();
		
		this->updateCrewId();
		this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->update();

		this->extremeSlowCache_lock.unlock();
		
		Sleep(500);

		
		
	}

}


void Client::update() {

	this->fastCache_lock.lock();
	this->slowCache_lock.lock();
	this->extremeSlowCache_lock.lock();

	if (this->p_UWorld != nullptr) {
		this->p_UWorld->update(Driver::base_address + Offsets::Process::UWorld);
	}
	else {
		this->p_UWorld = new UWorld(Driver::base_address + Offsets::Process::UWorld);
	}

	this->fastCache_lock.unlock();
	this->slowCache_lock.unlock();
	this->extremeSlowCache_lock.unlock();


}




void Client::updateLocalPlayer() {

	this->p_UWorld->p_UGameInstance->t_LocalPlayers->update();
	
	if (this->p_UWorld->c_LocalPlayer != nullptr)
		this->p_UWorld->c_LocalPlayer->update(this->p_UWorld->p_UGameInstance->t_LocalPlayers->at(0).p_address);
	else
		this->p_UWorld->c_LocalPlayer = new ULocalPlayer(this->p_UWorld->p_UGameInstance->t_LocalPlayers->at(0));
	
	
	for (AActor actor : this->p_UWorld->c_BP_PlayerPirate_C) {
		if (this->p_UWorld->c_LocalPlayer->PlayerController.Pawn.PlayerState.getName() == actor.Pawn.PlayerState.getName()) {
			if (this->p_UWorld->c_LocalActor == nullptr)
				this->p_UWorld->c_LocalActor = new AAthenaCharacter(actor.p_address);
			else
				this->p_UWorld->c_LocalActor->update(actor.p_address);
		}
	}

}



void Client::updateEnemies() {

	this->p_UWorld->c_Enemies.clear();

	for (AActor& actor : this->p_UWorld->c_BP_PlayerPirate_C) {
		if (!this->p_UWorld->isCrewMember(actor) && !this->p_UWorld->isLocalPlayer(actor))
			this->p_UWorld->c_Enemies.push_back(actor);
	}

}



void Client::updateLocalCrew() {

	std::vector <std::string> crew_mate_names = { };

	for (int x = 0; x < this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->size(); x++) {

		if (this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).CrewId == this->p_UWorld->c_LocalCrewId) {

			for (int y = 0; y < this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).t_Players.size(); y++) {
				crew_mate_names.push_back(this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).t_Players.at(y).getName());
			}

			this->p_UWorld->c_LocalCrew.clear();

			for (std::string& name : crew_mate_names) {

				for (AActor& actor : this->p_UWorld->c_BP_PlayerPirate_C) {

					if (name == actor.Pawn.PlayerState.getName() && !this->p_UWorld->isLocalPlayer(actor))
						this->p_UWorld->c_LocalCrew.push_back(actor);

					if (!(std::find(this->p_UWorld->c_LocalCrewNames.begin(), this->p_UWorld->c_LocalCrewNames.end(), name) != this->p_UWorld->c_LocalCrewNames.end()))
						this->p_UWorld->c_LocalCrewNames.push_back(name);

				}
			}

			return;
		}

	}

	

}


void Client::updateActors() {


	this->p_UWorld->refresh_BP_PlayerPirate_C();

	this->p_UWorld->t_Levels->update();


	for (int x = 0; x < this->p_UWorld->t_Levels->size(); x++) {

		try {

			this->p_UWorld->t_Levels->at(x).t_Actors.update();
			for (int y = 0; y < this->p_UWorld->t_Levels->at(x).t_Actors.size(); y++) {

				try {
					
					AActor actor = this->p_UWorld->t_Levels->at(x).t_Actors.at(y);
					if (actor.getClassName() == "BP_PlayerPirate_C" && !this->p_UWorld->containsActor(this->p_UWorld->c_BP_PlayerPirate_C, actor))
						this->p_UWorld->c_BP_PlayerPirate_C.push_back(actor);
					
				} catch (std::out_of_range e) { }

			}

		} catch (std::out_of_range e) { }

	}


}



void Client::updateActorsTest() {

	 
	this->p_UWorld->refresh_BP_PlayerPirate_C();
	 
	this->p_UWorld->t_Levels->update();
	 

	for (int x = 0; x < this->p_UWorld->t_Levels->size(); x++) {

		try {

			this->p_UWorld->t_Levels->at(x).t_Actors.update();
			for (int y = 0; y < this->p_UWorld->t_Levels->at(x).t_Actors.size(); y++) {

				try {

					AActor actor = this->p_UWorld->t_Levels->at(x).t_Actors.at(y);
					if (actor.getClassName() == "BP_PlayerPirate_C")
						this->p_UWorld->c_BP_PlayerPirate_C.push_back(actor);

				}
				catch (std::out_of_range e) {}

			}

		}
		catch (std::out_of_range e) {}

	}
	 

}





void Client::updateCrewId() {

	for (int x = 0; x < this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->size(); x++) {
		for (int y = 0; y < this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).t_Players.size(); y++) {

			std::string name = this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).t_Players.at(y).getName();

			if (this->p_UWorld->c_LocalActor->Pawn.PlayerState.getName() == name) {

				this->p_UWorld->c_LocalCrewId = this->p_UWorld->p_AAthenaGameState->p_ACrewService->t_Crews->at(x).CrewId;

			}

		}
	}

}