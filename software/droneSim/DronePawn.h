//Daniel Corrales 2023
//TFG UPM 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DronePawn.generated.h"

UCLASS()
class ADronePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADronePawn();

	//Functions to modify the speed on each axis
	void ModifySpeedX();
	void ModifySpeedNegativeX();
	void ModifySpeedY();
	void ModifySpeedNegativeY();
	void ModifySpeedZ();
	void ModifySpeedNegativeZ();
	void CalculateDelta();
	void CalculateVelocity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//Variables for speed control
	UPROPERTY(EditAnywhere)
	FVector realVelocity;

	UPROPERTY(EditAnywhere)
	FVector deltaVelocity;
	
	UPROPERTY(EditAnywhere)
	FVector targetVelocity;

	UPROPERTY(EditAnywhere) 
	float velocityConstant = 0.5f;

	UPROPERTY(EditAnywhere)
	float upperLimit = 1000.0f;

	UPROPERTY(EditAnywhere)
	float lowerLimit = -1000.0f;
	

};
