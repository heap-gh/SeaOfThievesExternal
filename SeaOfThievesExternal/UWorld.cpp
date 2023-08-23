
#include "UWorld.h"

UWorld::UWorld(UINT_PTR p_address) {

	this->p_address = p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);
	this->p_AAthenaGameState = new AAthenaGameState(this->d_address + Offsets::UWorld::GameState);
	this->p_UGameInstance = new UGameInstance(this->d_address + Offsets::UWorld::OwningWorldInstance);

	this->t_Levels = new TArray<ULevel>(this->d_address + Offsets::UWorld::Levels, 0x8);

}


void UWorld::update(UINT_PTR new_p_address) {

	this->p_address = new_p_address;
	this->d_address = Driver::read<UINT_PTR>(this->p_address);

	if (this->p_UGameInstance != nullptr)
		this->p_UGameInstance->update(this->d_address + Offsets::UWorld::OwningWorldInstance);
	else
		this->p_UGameInstance = new UGameInstance(this->d_address + Offsets::UWorld::OwningWorldInstance);


	if (this->p_AAthenaGameState != nullptr)
		this->p_AAthenaGameState->update(this->d_address + Offsets::UWorld::GameState);
	else
		this->p_AAthenaGameState = new AAthenaGameState(this->d_address + Offsets::UWorld::GameState);


	if (this->t_Levels != nullptr)
		this->t_Levels->update(this->d_address + Offsets::UWorld::Levels);
	else
		this->t_Levels = new TArray<ULevel>(this->d_address + Offsets::UWorld::Levels, 0x8);


}


UWorld::~UWorld() {

	delete this->p_UGameInstance;
	delete this->p_AAthenaGameState;
	delete this->t_Levels;

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
		if (_actor.Pawn.PlayerState.getId() == actor.Pawn.PlayerState.getId() || _actor.d_address == actor.d_address) {
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


bool UWorld::isDeleted() {

	if (this->d_address != Driver::read<UINT_PTR>(this->p_address))
		return true;

	return false;
}