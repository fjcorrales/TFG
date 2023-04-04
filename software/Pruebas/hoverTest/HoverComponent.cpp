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

	//Set Start location
	StartRelativeLocation = GetRelativeLocation();

	EndRelativeLocation = StartRelativeLocation;
	EndRelativeLocation.Z += 100.0f;
	
}


// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Compute and set current location
	SetRelativeLocation(EndRelativeLocation);
}

