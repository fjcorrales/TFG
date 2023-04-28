// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawnCom.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


// Sets default values
ADronePawnCom::ADronePawnCom()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADronePawnCom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADronePawnCom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADronePawnCom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

