//Daniel Corrales 2023
//TFG UPM 


#include "HoverComponent.h"


// Sets default values for this component's properties
UHoverComponent::UHoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHoverComponent::InputHover(UInputComponent *PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Hover", IE_Pressed, this, &UHoverComponent::SetHover);
}

void UHoverComponent::SetHover()
{
	TriggerHover = true;
}

void UHoverComponent::Hover(float DeltaTime)
{
	//Establecemos la altura actual
	ActualHeight += DeltaTime * Speed * 1;
	//Computamos y actualizamos la ubicacion en caso de no haber llegado a la altura maxima
	if(ActualHeight <= MaxHeight || ActualHeight <= 0.0f){
		SetRelativeLocation(StartRelativeLocation + HeightNorm * ActualHeight);
	}
}

void UHoverComponent::ResetPosition()
{
	FVector start;
	start.X = 0;
	start.Y = 0;
	start.Z = 40.0f;
	SetRelativeLocation(start);
}


// Called when the game starts
void UHoverComponent::BeginPlay()
{
	Super::BeginPlay();

	//Obtenemos la ubicacion inicial del dron
	StartRelativeLocation = GetRelativeLocation();
	

	//Computamos el movimiento normalizado y la ubicacion final del dron
	HeightNorm = StartRelativeLocation;
	HeightNorm.Z += Height;
	HeightNorm.Normalize();
	MaxHeight = Height;
}

// Called every frame
void UHoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(TriggerHover && !Reset)
	{
		Hover(DeltaTime);
	}

	if(Reset && !TriggerHover)
	{
		ResetPosition();
	}
}
