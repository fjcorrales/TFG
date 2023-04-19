//Daniel Corrales 2023
//TFG UPM 


#include "move.h"


// Sets default values for this component's properties
Umove::Umove()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void Umove::EnableMovement(bool shouldMove)
{
	// Assing value and set correct tick enable state
	MoveEnable = shouldMove;
	SetComponentTickEnabled(MoveEnable);
}

void Umove::ResetMovement()
{
	//Clear distance and set to origin
	CurDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}

void Umove::SetMoveDirection(int Direction)
{
	MoveDirection = Direction >= 1 ? 1 : -1;
}

// Called when the game starts
void Umove::BeginPlay()
{
	Super::BeginPlay();

	// Set start location
	StartRelativeLocation = this->GetRelativeLocation();

	//Compute normalized movement
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDistance = MoveOffset.Size();

	//Check if ticking is required
	SetComponentTickEnabled(MoveEnable);

}


// Called every frame
void Umove::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Set the current distance
	if(MoveEnable)
	{
		CurDistance += DeltaTime * Speed * MoveDirection;
		if(CurDistance >= MaxDistance || CurDistance <= 0.0f){
			//Inver direction
			MoveDirection *= -1;

			//Fire event
			OnEndpointReached.Broadcast(CurDistance >= MaxDistance);

			//Clamp distance
			CurDistance = FMath::Clamp(CurDistance, 0.0f, MaxDistance);
		}
	}
	

	// Compute and sert current location
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurDistance);
}


