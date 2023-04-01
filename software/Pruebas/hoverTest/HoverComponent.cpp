// Fill out your copyright notice in the Description page of Project Settings.


#include "HoverComponent.h"


// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	// Conseguimos la posicion de inicio del objeto
	StartRelLocation = this->GetRelativeLocation();

	//Compute normalized movement
	MoveOffset.Z = MaxHeight;
	MoveOffset.X = 1.0f;
	MoveOffset.Y = 1.0f;
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDistance = MoveOffset.Size();

	//Seteamos el tick a true
	SetComponentTickEnabled(true);
	
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// En base a la altura especificada en la variable Height, subimos al dron a esa altura y hacemos que oscile ligeramente en el sitio
	CurDistance += DeltaTime * Speed * MoveDirection;
		if(CurDistance >= MaxDistance || CurDistance <= 0.0f){

			//Clamp distance
			CurDistance = FMath::Clamp(CurDistance, 0.0f, MaxDistance);
		}

	// Compute and sert current location
	SetRelativeLocation(StartRelLocation + MoveOffsetNorm * CurDistance);
}

