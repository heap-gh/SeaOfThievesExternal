#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"
#include "UWorld.h"
#include "Aimbot.h"

struct ClientSettings {

	bool aimbot = false;


};



class Client {


public:

	std::mutex fastCache_lock;
	std::mutex slowCache_lock;
	std::mutex extremeSlowCache_lock;

	UWorld* p_UWorld = nullptr;
	Aimbot* p_Aimbot = nullptr;

	ClientSettings* client_settings = nullptr;
	AimbotSettings* aimbot_settings = nullptr;

public:

	Client();
	~Client();

	void init();
	void start();
	void update();
	void initLocalPlayer();
	void initGame();
	void initAimbot();
	void loadClientSettings();
	void loadAimbotSettings();

	void testing();

	void caching();
	void fastCache();
	void slowCache();
	void extremeSlowCache();
	void worldCache();

	// caching

	void updateCrewId();
	void updateActors();
	void updateLocalPlayer();
	void updateLocalCrew();
	void updateEnemies();
	
	void updateActorsTest();


};


#endif // !CLIENT_H

