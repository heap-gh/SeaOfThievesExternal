#pragma once

#ifndef CLIENT_H
#define CLIENT_H

#include "includes.h"
#include "UWorld.h"
#include "Aimbot.h"

class Client {


public:

	std::mutex fastCache_lock;
	std::mutex slowCache_lock;
	

	UWorld* p_UWorld = nullptr;
	Aimbot* aimbot = nullptr;


public:

	Client();
	~Client();

	void init();
	void start();
	void update();


	void caching();
	void fastCache();
	void slowCache();
	void extremeSlowCache();

};


#endif // !CLIENT_H

