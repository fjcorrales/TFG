//Daniel Corrales 2023
//TFG UPM 

#include "DronePawn.h"

// Sets default values
ADronePawn::ADronePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	realVelocity = GetActorLocation() * DeltaTime;
	CalculateDelta();
	CalculateVelocity(); //CalculateVelocity
	FVector pos = GetActorLocation();
	pos += DeltaTime*realVelocity;
	SetActorLocation(pos);
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();

	targetVelocity = {0.0f, 0.0f, 0.0f};
}

// Called to bind functionality to input
void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Setting up bindings to add or subtract from the targetVelocity
	PlayerInputComponent->BindAction("XPositive", IE_Pressed, this, &ADronePawn::ModifySpeedX);
	PlayerInputComponent->BindAction("XNegative", IE_Pressed, this, &ADronePawn::ModifySpeedNegativeX);
	PlayerInputComponent->BindAction("YPositive", IE_Pressed, this, &ADronePawn::ModifySpeedY);
	PlayerInputComponent->BindAction("YNegative", IE_Pressed, this, &ADronePawn::ModifySpeedNegativeY);
	PlayerInputComponent->BindAction("ZPositive", IE_Pressed, this, &ADronePawn::ModifySpeedZ);
	PlayerInputComponent->BindAction("ZNegative", IE_Pressed, this, &ADronePawn::ModifySpeedNegativeZ);
}


//Functions to set the speed with keyboard presses
void ADronePawn::ModifySpeedX()
{
	targetVelocity.X += 10.0f;
}

void ADronePawn::ModifySpeedNegativeX()
{
	targetVelocity.X -= 10.0f;
}

void ADronePawn::ModifySpeedY()
{
	targetVelocity.Y += 10.0f;
}

void ADronePawn::ModifySpeedNegativeY()
{
	targetVelocity.Y -= 10.0f;
}

void ADronePawn::ModifySpeedZ()
{
	targetVelocity.Z += 10.0f;
}

void ADronePawn::ModifySpeedNegativeZ()
{
	targetVelocity.Z -= 10.0f;
}

/*
Function to calculate the change needed in the velocity in order to 
get the drone to the target velocity
*/
void ADronePawn::CalculateDelta()
{
	deltaVelocity = (targetVelocity - realVelocity) * velocityConstant;
}

/*
Function to add to the realVelocity the values needed
to make the drone reach the intended velocity
*/
void ADronePawn::CalculateVelocity()
{
	if(deltaVelocity.X >= upperLimit)
	{
		deltaVelocity.X = upperLimit;
	}
	if(deltaVelocity.X <= lowerLimit)
	{
		deltaVelocity.X = lowerLimit;
	}
	if(deltaVelocity.Y >= upperLimit)
	{
		deltaVelocity.Y = upperLimit;
	}
	if(deltaVelocity.Y <= lowerLimit)
	{
		deltaVelocity.Y = lowerLimit;
	}
	if(deltaVelocity.Z >= upperLimit)
	{
		deltaVelocity.Z = upperLimit;
	}
	if(deltaVelocity.Z <= lowerLimit)
	{
		deltaVelocity.Z = lowerLimit;
	}

	realVelocity += deltaVelocity;
}
