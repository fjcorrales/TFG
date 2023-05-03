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
	~ADronePawnCom();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
//Here i'll define all the variables needed inside the pawn built to test the communication
	void *handle; 

	typedef int (*fun_dummy)(int num);
	fun_dummy dummy;
	
	//Start function, sets the listener up
	typedef void *(*fun_start)();
	fun_start start;

	//struct which holds the information needed in the update function
	 struct vector3_transfer
    {
        float x, y, z;
    };
	typedef struct vector3_transfer vector3_transfer;

	//Update function will be called in the tick, used for recieving info from talker/publisher
	typedef int (*fun_update)(vector3_transfer *, void *subscriber);	
	fun_update update;

	//End function for closing the library 
	typedef void (*fun_end)();
	fun_end end;
};
