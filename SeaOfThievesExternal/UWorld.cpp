
#include "UWorld.h"

UWorld::UWorld(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);
	this->p_AAthenaGameState = new AAthenaGameState(this->d_address + Offsets::UWorld::GameState);
	this->p_UGameInstance = new UGameInstance(this->d_address + Offsets::UWorld::OwningWorldInstance);

	this->t_Levels = TArray<ULevel>(this->d_address + Offsets::UWorld::Levels, 0x8);

}


UWorld::~UWorld() {



}


void UWorld::updateLocalPlayer() {

	std::string localname = this->p_UGameInstance->t_LocalPlayers.at(0).PlayerController.Pawn.PlayerState.getName();

	for (AActor actor : this->c_BP_PlayerPirate_C) {
		if (localname == actor.Pawn.PlayerState.getName()) {
			this->c_LocalPlayer = actor;
			break;
		}
	}

}



void UWorld::updateEnemies() {

	this->c_Enemies.clear();

	for (AActor& actor : this->c_BP_PlayerPirate_C) {
		if (!isCrewMember(actor) && !isLocalPlayer(actor))
			this->c_Enemies.push_back(actor);
	}

}



void UWorld::updateLocalCrew() {

	std::vector <std::string> crew_mate_names = { };

	for (int x = 0; x < this->p_AAthenaGameState->p_ACrewService.t_Crews.size(); x++) {
		
		if (this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).CrewId == this->c_LocalCrewId) {

			for (int y = 0; y < this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).t_Players.size(); y++) {
				crew_mate_names.push_back(this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).t_Players.at(y).getName());
			}
			
			this->c_LocalCrew.clear();
		
			for (std::string& name : crew_mate_names) {
		
				for (AActor& actor : this->c_BP_PlayerPirate_C) {
					
					if (name == actor.Pawn.PlayerState.getName() && !isLocalPlayer(actor))
						this->c_LocalCrew.push_back(actor);

					if (!(std::find(this->c_LocalCrewNames.begin(), this->c_LocalCrewNames.end(), name) != this->c_LocalCrewNames.end()))
						this->c_LocalCrewNames.push_back(name);
					
				}
			}
			
			return;
		}

	}

	
}


void UWorld::updateActors() {

	refresh_BP_PlayerPirate_C();
	this->t_Levels.update(); 
	this->p_UGameInstance->t_LocalPlayers.update();

	for (int x = 0; x < this->t_Levels.size(); x++) {

		try {

			this->t_Levels.at(x).t_Actors.update();

			for (int y = 0; y < this->t_Levels.at(x).t_Actors.size(); y++) {


				try {
					AActor actor = this->t_Levels.at(x).t_Actors.at(y);
					if (actor.getClassName() == "BP_PlayerPirate_C" && !containsActor(this->c_BP_PlayerPirate_C, actor)) {
						this->c_BP_PlayerPirate_C.push_back(actor);
					}
				}
				catch (std::out_of_range e) {

				}

			}

		}
		catch (std::out_of_range e) {

		}

	}

}




void UWorld::updateCrewId() {


	for (int x = 0; x < this->p_AAthenaGameState->p_ACrewService.t_Crews.size(); x++) {
		for (int y = 0; y < this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).t_Players.size(); y++) {

			std::string name = this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).t_Players.at(y).getName();

			if (this->c_LocalPlayer.Pawn.PlayerState.getName() == name) {

				this->c_LocalCrewId = this->p_AAthenaGameState->p_ACrewService.t_Crews.at(x).CrewId;

			}
		}
	}

}



bool UWorld::isLocalPlayer(AActor& actor) {

	if (this->c_LocalPlayer.Pawn.PlayerState.getName() == actor.Pawn.PlayerState.getName())
		return true;

	return false;

}


bool UWorld::isCrewMember(AActor& actor) {

	std::string target_name = actor.Pawn.PlayerState.getName();

	for (std::string& crew_actor : this->c_LocalCrewNames) {
		if (target_name == crew_actor || target_name == this->c_LocalPlayer.Pawn.PlayerState.getName())
			return true;
	}

	return false;

}



bool UWorld::containsActor(std::vector<AActor>& actor_list, AActor& actor) {

	for (AActor& _actor : actor_list) {
		if (_actor.Pawn.PlayerState.getId() == actor.Pawn.PlayerState.getId()) {
			return true;
		}
	}

	return false;
}


void UWorld::refresh_BP_PlayerPirate_C() {

	for (int x = 0; x < this->c_BP_PlayerPirate_C.size(); x++) {
	
		if (this->c_BP_PlayerPirate_C.at(x).isDeleted())
			deleteElementByIndex(this->c_BP_PlayerPirate_C, x);


	}

}



template<class T>
void UWorld::deleteElementByIndex(std::vector<T>& vec, size_t index) {
	if (index < vec.size()) {
		vec.erase(vec.begin() + index);
	}

}



void UWorld::updateWorld() {

	this->d_address = Driver::read<UINT_PTR>(this->p_address);
	
	if (this->p_AAthenaGameState->isDeleted()) {
		delete this->p_AAthenaGameState;
		this->p_AAthenaGameState = new AAthenaGameState(this->d_address + Offsets::UWorld::GameState);

	}

	if (this->p_UGameInstance->isDeleted()) {
		delete this->p_UGameInstance;
		this->p_UGameInstance = new UGameInstance(this->d_address + Offsets::UWorld::OwningWorldInstance);
	}

}



bool UWorld::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}