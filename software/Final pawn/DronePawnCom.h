// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DronePawnCom.generated.h"


UCLASS()
class ADronePawnCom : public APawn
{
	GENERATED_BODY()

public:
	// Constructor
	ADronePawnCom();	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when the game is finished, modified to execute the end() function od the 
	//ROS library to shut down the listener. After that, the library is closed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	//Sets up components, called inside the constructor
	void setComponents();

	//Function to open the dynamic library and import its functions called in the BeginPlay
	void dlImport();

	//Function that moves the drone called in the Tick() function
	void move(FVector pos1);

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

	

//Section 2, here i'll declare the variables needed for moving the drone 

	//Arm component to have a static camera attached to it
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Cam,meta=(AllowPrivateAccess = "true"))
	class USpringArmComponent* arm;

	//To attarch to the arm component and visualize the mesh
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Cam,meta=(AllowPrivateAccess = "true"))
	class UCameraComponent* camera;

	//Drone Mesh
	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* MeshComponent; 

	//Starting location of the drone on each frame 
	FVector StartRelLocation;

	//Normalized vector to set the movement each frame (for a fluid moving animation)
	FVector MoveOffsetNorm;
	
	//Coordinates wich will be recieved by the subscriptor and managed by the update function
	vector3_transfer coordinates;
	
	//Vector used to update the position of the pawn
	UPROPERTY(EditAnywhere)
	FVector pos;

};
