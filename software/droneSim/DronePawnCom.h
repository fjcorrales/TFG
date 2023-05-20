// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DronePawnCom.generated.h"


UCLASS()
class DRONESIM_API ADronePawnCom : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADronePawnCom();	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
//Section 1: Here i'll define all the variables needed inside the pawn built to test the communication
	void *handle; 
	
	//Start function, sets the listener up
	typedef void (*fun_start)();
	fun_start start;

	//struct which holds the information needed in the update function
	 struct vector3_transfer
    {
        float x, y, z;
    };
	typedef struct vector3_transfer vector3_transfer;

	//Update function will be called in the tick, used for recieving info from talker/publisher
	typedef int (*fun_update)(vector3_transfer *);	
	fun_update update;

	//End function for closing the library 
	typedef void (*fun_end)();
	fun_end end;

	//Coordinates wich will be recieved by the subscriptor and managed by the update function
	vector3_transfer coordinates;
	
	//Vector used to update the position of the pawn
	UPROPERTY(EditAnywhere)
	FVector pos;

//Section 2, here i'll declare the variables needed for the moving the drone part
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Cam,meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* arm;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Cam,meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* camera;
	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent; 
	FVector StartRelLocation;
	FVector MoveOffsetNorm;
	float CurrDistance;
	float Speed = 100.f;
	float MaxDistance = 0.0f;
};
