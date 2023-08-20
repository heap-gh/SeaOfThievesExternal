#pragma once


/*

t_<name>			= TArray
p_<name>			= Pointer
d_<name>			= dereferenced Pointer
f_<name>			= FString
b_<name>			= base address
c_<name>			= cached data

Local ViewAngles		 FRotation  f   = this->p_UWorld->p_UGameInstance->t_LocalPlayers.at(0).p_APlayerController->p_APlayerCameraManager->getViewAngles();
PlayerPosition  		 FVector    ad  = p_UWorld->t_Levels.at(x).t_Actors.at(y).RootComponent.getCoords();


_________________________________________________________________

CLASS TEMPLATES

		#pragma once

		#ifndef SOMECLASS_H
		#define SOMECLASS_H

		#include <Windows.h>

		class SOMECLASS {

		public:

			bool initialized = false;

			UINT_PTR p_address;
			UINT_PTR d_address;


		public:

			SOMECLASS();
			SOMECLASS(UINT_PTR p_address);

		};

		#endif // !SOMECLASS_H


_________________________________________________________________________


*/