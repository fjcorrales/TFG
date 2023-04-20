// Copyright Epic Games, Inc. All Rights Reserved.
//Daniel Corrales 2023
//TFG UPM 

#pragma once

#include "CoreMinimal.h"
#include "DronePawn.h"
#include "GameFramework/GameModeBase.h"
#include "droneSimGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DRONESIM_API AdroneSimGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	//Creamos un constructor para que nos cargue el dronePawn como el default pawn del juego
public: 
	AdroneSimGameModeBase();
};
