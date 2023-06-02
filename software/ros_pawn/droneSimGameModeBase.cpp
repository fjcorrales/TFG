// Copyright Epic Games, Inc. All Rights Reserved.


#include "droneSimGameModeBase.h"
#include "DronePawn.h"
#include "DronePawnCom.h"


AdroneSimGameModeBase::AdroneSimGameModeBase()
{
    //Instanciamos que el default pawn sea el dron                                      
    static ConstructorHelpers::FClassFinder<APawn> DronePawnComBP(TEXT("/Game/Blueprints/DronePawnComBP"));
    if(DronePawnComBP.Class != NULL)
    {
        DefaultPawnClass = DronePawnComBP.Class;
    }
    //DefaultPawnClass = ADronePawnCom::StaticClass();
}
