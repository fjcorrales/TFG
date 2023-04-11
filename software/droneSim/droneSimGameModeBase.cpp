// Copyright Epic Games, Inc. All Rights Reserved.


#include "droneSimGameModeBase.h"
#include "DronePawn.h"

AdroneSimGameModeBase::AdroneSimGameModeBase()
{
    //Instanciamos que el default pawn sea el dron
    DefaultPawnClass = ADronePawn::StaticClass();
}
