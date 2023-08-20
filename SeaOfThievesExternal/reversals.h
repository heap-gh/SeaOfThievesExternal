#pragma once


#ifndef REVERSALS_H
#define REVERSALS_H

#include <Windows.h>


namespace Offsets
{

	namespace Process {

		const UINT_PTR GNames = 0x84d58e8;
		const UINT_PTR GObjects = 0x84d9f20;
		const UINT_PTR UWorld = 0x859d350;

	}

	// Inheritance: UObject
	namespace UWorld
	{

		constexpr auto GameState = 0x58; // AGameState*
		constexpr auto Levels = 0x150; // TArray<ULevel*>
		constexpr auto OwningWorldInstance = 0x1C0; // UGameInstance*

	}
	

	// GET CREWS
	// Gamestate] + 0x608 CrewService] + 0x4A0 Crews] + TArray<Crew>[idx] + 0x20 Players] + TArray<Player*>

	namespace AAthenaGameState
	{
		
		constexpr auto CrewService = 0x608; // ACrewService*
		
	}

	namespace ACrewService
	{

		constexpr auto Crews = 0x4a0; // TArray<FCrew>

	}

	namespace FCrew
	{

		constexpr auto CrewId = 0x0; // FGuid
		constexpr auto SessionId = 0x10; // FGuid
		constexpr auto Players = 0x20; // TArray<APlayerState*>
		constexpr auto CrewSessionTemplate = 0x30; // FCrewSessionTemplate
		constexpr auto LiveryID = 0x68; // FGuid
		constexpr auto AssociatedActors = 0x80; // TArray<AActor*>
		constexpr auto HasEverSetSail = 0x90; // bool
		constexpr auto ScrambleNameIndex = 0x94; // int32_t

	}

	namespace APlayerState
	{
		constexpr auto Score = 0x3c8; // float
		constexpr auto Ping = 0x3cc; // char
		constexpr auto PlayerName = 0x3d0; // FString*
		constexpr auto PlayerId = 0x3f0; // int32_t
		constexpr auto bIsSpectator = 0x3f4; // char : 1
		constexpr auto bOnlySpectator = 0x3f4; // char : 1
		constexpr auto bIsABot = 0x3f4; // char : 1
		constexpr auto bIsInactive = 0x3f4; // char : 1
		constexpr auto bFromPreviousLevel = 0x3f4; // char : 1
		constexpr auto StartTime = 0x3f8; // int32_t
		constexpr auto EngineMessageClass = 0x400; // ULocalMessage*
		constexpr auto UniqueId = 0x420; // FUniqueNetIdRepl

	}

	namespace ULevel
	{
		constexpr auto Actors = 0xa0; // TArray<AActor*>
		constexpr auto ActorCluster = 0xc8; // ULevelActorContainer*
		constexpr auto OwningWorld = 0xd0; // UWorld*
		constexpr auto Model = 0xd8; // UModel*
		constexpr auto ModelComponents = 0xe0; // TArray<UModelComponent*>
		constexpr auto LevelScriptActor = 0xf0; // ALevelScriptActor*
		constexpr auto NavListStart = 0xf8; // ANavigationObjectBase*
		constexpr auto NavListEnd = 0x100; // ANavigationObjectBase*
		constexpr auto NavDataChunks = 0x108; // TArray<UNavigationDataChunk*>
		constexpr auto LightmapTotalSize = 0x118; // float
		constexpr auto ShadowmapTotalSize = 0x11c; // float
		constexpr auto StaticNavigableGeometry = 0x120; // TArray<FVector>
		constexpr auto LevelVisibility = 0x260; // bool
		constexpr auto Blocked = 0x270; // char : 1
		constexpr auto AssetUserData = 0x2d8; // TArray<UAssetUserData*>
	}

	namespace AActor
	{
		constexpr auto ActorID = 0x18; 
		constexpr auto PrimaryActorTick = 0x28; // FActorTickFunction
		constexpr auto CustomTimeDilation = 0x78; // float
		constexpr auto bAllowRemovalFromServerWhenCollisionMerged = 0x7c; // char : 1
		constexpr auto bAllowRemovalFromServerWhenAutomaticallyInstanced = 0x7c; // char : 1
		constexpr auto bHidden = 0x7c; // char : 1
		constexpr auto bNetTemporary = 0x7c; // char : 1
		constexpr auto bNetStartup = 0x7c; // char : 1
		constexpr auto bOnlyRelevantToOwner = 0x7c; // char : 1
		constexpr auto bAlwaysRelevant = 0x7c; // char : 1
		constexpr auto bReplicateMovement = 0x7c; // char : 1
		constexpr auto bTearOff = 0x7d; // char : 1
		constexpr auto bExchangedRoles = 0x7d; // char : 1
		constexpr auto bPendingNetUpdate = 0x7d; // char : 1
		constexpr auto bNetLoadOnClient = 0x7d; // char : 1
		constexpr auto bNetUseOwnerRelevancy = 0x7d; // char : 1
		constexpr auto bBlockInput = 0x7d; // char : 1
		constexpr auto bCanBeInCluster = 0x7d; // char : 1
		constexpr auto bActorEnableCollision = 0x7e; // char : 1
		constexpr auto bReplicateAttachment = 0x7e; // char : 1
		constexpr auto bReplicates = 0x7e; // char : 1
		constexpr auto OnPreNetOwnershipChange = 0x80; // FScriptMulticastDelegate
		constexpr auto RemoteRole = 0x83; // ENetRole
		constexpr auto Owner = 0x88; // AActor*
		constexpr auto ReplicatedMovement = 0x90; // FRepMovement
		constexpr auto AttachmentReplication = 0xc8; // FRepAttachment
		constexpr auto Role = 0x110; // ENetRole
		constexpr auto SpawnRestrictions = 0x112; // EActorSpawnRestrictions
		constexpr auto AutoReceiveInput = 0x113; // EAutoReceiveInput
		constexpr auto InputPriority = 0x114; // int32_t
		constexpr auto InputComponent = 0x118; // UInputComponent*
		constexpr auto NetCullDistanceSquared = 0x120; // float
		constexpr auto NetTag = 0x128; // int32_t
		constexpr auto NetUpdateTime = 0x12c; // float
		constexpr auto NetUpdateFrequency = 0x130; // float
		constexpr auto NetPriority = 0x134; // float
		constexpr auto LastNetUpdateTime = 0x138; // float
		constexpr auto NetDriverName = 0x13c; // FName
		constexpr auto bAutoDestroyWhenFinished = 0x144; // char : 1
		constexpr auto bCanBeDamaged = 0x144; // char : 1
		constexpr auto bActorIsBeingDestroyed = 0x144; // char : 1
		constexpr auto bCollideWhenPlacing = 0x144; // char : 1
		constexpr auto bFindCameraComponentWhenViewTarget = 0x144; // char : 1
		constexpr auto bRelevantForNetworkReplays = 0x144; // char : 1
		constexpr auto SpawnCollisionHandlingMethod = 0x148; // ESpawnActorCollisionHandlingMethod
		constexpr auto Instigator = 0x150; // APawn*
		constexpr auto Children = 0x158; // TArray<AActor*>
		constexpr auto RootComponent = 0x168; // USceneComponent*
		constexpr auto ControllingMatineeActors = 0x170; // TArray<AMatineeActor*>
		constexpr auto InitialLifeSpan = 0x180; // float
		constexpr auto bAllowReceiveTickEventOnDedicatedServer = 0x188; // char : 1
		constexpr auto Layers = 0x190; // TArray<FName>
		constexpr auto ParentComponentActor = 0x1a0; // FActorPtr
		constexpr auto ChildComponentActors = 0x1a8; // TArray<TWeakObjectPtr<AActor>>
		constexpr auto bActorSeamlessTraveled = 0x1c0; // char : 1
		constexpr auto bIgnoresOriginShifting = 0x1c0; // char : 1
		constexpr auto bEnableAutoLODGeneration = 0x1c0; // char : 1
		constexpr auto InvertFeatureCheck = 0x1c0; // char : 1
		constexpr auto Feature = 0x1c4; // FName
		constexpr auto Tags = 0x1d0; // TArray<FName>
		constexpr auto HiddenEditorViews = 0x1e0; // uint64_t
		constexpr auto OnActorBeginOverlap = 0x1e8; // FScriptMulticastDelegate
		constexpr auto OnActorEndOverlap = 0x1e9; // FScriptMulticastDelegate
		constexpr auto OnActorHit = 0x1ea; // FScriptMulticastDelegate
		constexpr auto OnDestroyed = 0x1eb; // FScriptMulticastDelegate
		constexpr auto OnEndPlay = 0x228; // FScriptMulticastDelegate
		constexpr auto bDoOverlapNotifiesOnLoad = 0x229; // bool
		constexpr auto BlueprintCreatedComponents = 0x320; // TArray<UActorComponent*>
		constexpr auto InstanceComponents = 0x330; // TArray<UActorComponent*>
		constexpr auto ChildActorInterfaceProviders = 0x348; // TArray<AActor*>
		constexpr auto DormancyLingeringInSeconds = 0x3c0; // double
	}

	namespace USceneComponent
	{
		constexpr auto Coords = 0x12C; //FVector
		constexpr auto AttachChildren = 0xc8; // TArray<USceneComponent*>
		constexpr auto bRequiresCustomLocation = 0xd8; // char : 1
		constexpr auto AttachParent = 0xe0; // USceneComponent*
		constexpr auto AttachSocketName = 0xe8; // FName
		constexpr auto bAbsoluteLocation = 0xf0; // char : 1
		constexpr auto bAbsoluteRotation = 0xf0; // char : 1
		constexpr auto bAbsoluteScale = 0xf0; // char : 1
		constexpr auto bVisible = 0xf0; // char : 1
		constexpr auto bAbsoluteTranslation = 0xf0; // char : 1
		constexpr auto bHiddenInGame = 0xf0; // char : 1
		constexpr auto bShouldUpdatePhysicsVolume = 0xf0; // char : 1
		constexpr auto bBoundsChangeTriggersStreamingDataRebuild = 0xf0; // char : 1
		constexpr auto bUseAttachParentBound = 0xf1; // char : 1
		constexpr auto bComponentIsUnionOfChildren = 0xf1; // char : 1
		constexpr auto bJitterReduction = 0xf1; // char : 1
		constexpr auto CacheRootVelocity = 0xf1; // char : 1
		constexpr auto bWorldToComponentUpdated = 0xf1; // char : 1
		constexpr auto PhysicsVolume = 0x100; // TWeakObjectPtr<APhysicsVolume>
		constexpr auto RelativeLocation = 0x108; // FVector
		constexpr auto RelativeRotation = 0x114; // FRotator
		constexpr auto RelativeScale3D = 0x120; // FVector
		constexpr auto Mobility = 0x230; // EComponentMobility
		constexpr auto DetailMode = 0x231; // EDetailMode
		constexpr auto ComponentVelocity = 0x23c; // FVector
		constexpr auto PhysicsVolumeChangedDelegate = 0x248; // FScriptMulticastDelegate
		constexpr auto SocketVelocitiesToCache = 0x268; // TArray<FName>
		constexpr auto MovedActors = 0x278; // TArray<AActor*>
	}


	namespace UGameInstance
	{
		constexpr auto LocalPlayers = 0x38; // TArray<ULocalPlayer*>
		constexpr auto OnlineSession = 0x50; // UOnlineSession*
	}

	namespace ULocalPlayer
	{

		constexpr auto PlayerController = 0x30; // APlayerController*
		constexpr auto ViewportClient = 0x60; // UGameViewportClient*
		constexpr auto AspectRatioAxisConstraint = 0xa8; // EAspectRatioAxisConstraint
		constexpr auto PendingLevelPlayerControllerClass = 0xb0; // APlayerController*
		constexpr auto bSentSplitJoin = 0xb8; // char : 1
		constexpr auto MinimumAspectRatio = 0xbc; // float
	}

	namespace APlayerController
	{
		constexpr auto Pawn = 0x438; // APawn*
		constexpr auto CameraManager = 0x458; // PlayerCameraManager *

	}

	namespace APlayerCameraManager
	{
		constexpr auto CameraCache = 0x45C; // FRotator;

	}

	namespace APawn
	{
		constexpr auto bUseControllerRotationPitch = 0x3d0; // char : 1
		constexpr auto bUseControllerRotationYaw = 0x3d0; // char : 1
		constexpr auto bUseControllerRotationRoll = 0x3d0; // char : 1
		constexpr auto bCanAffectNavigationGeneration = 0x3d0; // char : 1
		constexpr auto BaseEyeHeight = 0x3d4; // float
		constexpr auto AutoPossessPlayer = 0x3d8; // EAutoReceiveInput
		constexpr auto AutoPossessAI = 0x3d9; // EAutoPossessAI
		constexpr auto AIControllerClass = 0x3e0; // AController*
		constexpr auto PlayerState = 0x3e8; // APlayerState*
		constexpr auto RemoteViewPitch = 0x3f0; // char
		constexpr auto LastHitBy = 0x3f8; // AController*
		constexpr auto Controller = 0x400; // AController*
		constexpr auto ControlInputVector = 0x420; // FVector
		constexpr auto LastControlInputVector = 0x42c; // FVector
	}


};








#endif // !REVERSALS_H
