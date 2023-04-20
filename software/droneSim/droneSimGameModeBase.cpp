// Copyright Epic Games, Inc. All Rights Reserved.
//Daniel Corrales 2023
//TFG UPM 


#include "droneSimGameModeBase.h"
#include "DronePawn.h"

AdroneSimGameModeBase::AdroneSimGameModeBase()
{
    //Instanciamos que el default pawn sea el dron
    DefaultPawnClass = ADronePawn::StaticClass();
}
