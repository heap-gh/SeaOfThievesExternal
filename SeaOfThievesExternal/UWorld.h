#pragma once


#ifndef UWORLD_H
#define UWORLD_H

#include <thread>
#include <mutex>
#include <algorithm>


#include "includes.h"
#include "AAthenaGameState.h"
#include "UGameInstance.h"

class UWorld {

public:

	std::mutex lock;

	UINT_PTR p_address;
	UINT_PTR d_address;

	UGameInstance* p_UGameInstance;
	AAthenaGameState* p_AAthenaGameState;
	TArray<ULevel> t_Levels;

	// CACHED DATA

	FGuid c_LocalCrewId;
	AActor c_LocalPlayer;
	std::vector<AActor> c_BP_PlayerPirate_C;
	std::vector<std::string> c_BP_PlayerPirate_CNames;
	std::vector<AActor> c_LocalCrew; // includes localPlayer
	std::vector<std::string> c_LocalCrewNames;
	std::vector<AActor> c_Enemies;

public:

	UWorld(UINT_PTR m_address);
	~UWorld();

	bool isLocalPlayer(AActor& actor);
	bool isCrewMember(AActor& actor);
	bool containsActor(std::vector<AActor>& actor_list, AActor& actor);
	void refresh_BP_PlayerPirate_C();
	template <class T>
	void deleteElementByIndex(std::vector<T>& vec, size_t index);
	bool isDeleted();

	

};


#endif // !UWORLD_H
