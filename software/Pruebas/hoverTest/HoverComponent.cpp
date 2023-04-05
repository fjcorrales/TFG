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

	//Obtenemos la ubicacion inicial del dron
	StartRelativeLocation = GetRelativeLocation();

	//Computamos el movimiento normalizado y la ubicacion final del dron
	EndRelativeLocation = StartRelativeLocation;
	EndRelativeLocation.Z += Height;
	HeightNorm = EndRelativeLocation;
	HeightNorm.Normalize();
	MaxHeight = Height;


	
	
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Establecemos la altura actual
	ActualHeight += DeltaTime * Speed;
	//Computamos y actualizamos la ubicacion en caso de no haber llegado a la altura maxima
	if(ActualHeight <= MaxHeight || ActualHeight <= 0.0f){
		SetRelativeLocation(StartRelativeLocation + HeightNorm * ActualHeight);
	}
}

