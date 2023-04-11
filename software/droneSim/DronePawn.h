// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DronePawn.generated.h"

UCLASS()
class DRONESIM_API ADronePawn : public APawn
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
	FVector realVelocity;
	FVector targetVelocity;
	FVector deltaVelocity;

	UPROPERTY(EditAnywhere) 
	float velocityConstant;

	UPROPERTY(EditAnywhere)
	float upperLimit;

	UPROPERTY(EditAnywhere)
	float lowerLimit;
	

};
