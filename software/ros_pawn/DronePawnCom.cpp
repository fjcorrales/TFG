// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawnCom.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values
ADronePawnCom::ADronePawnCom()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    //We call the setComponents function to set up all the pawns components
    setComponents();
}

// Called when the game starts or when spawned
void ADronePawnCom::BeginPlay()
{

	Super::BeginPlay();
    //We call the dlImport to open the ros2 library
	dlImport();
    //Here since unreal only executes this begin play once and at the start of the level
    //we call the start function which sets up the listener in order to recieve the 
    //coordinates from the ROS2 publisher/talker
    start();

}

// Called every frame
void ADronePawnCom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //In here, we call the update function which will be constantly looking at the queue 
    //of published messages from the publisher in order to recieve the coordiantes
    update(&coordinates);
	//We store the vector mevement
    pos.X=coordinates.x;
    pos.Y=coordinates.y;
    pos.Z=coordinates.z;
    //And with the postition vector created, we call the move function
    move(pos);
	
}

// Called to bind functionality to input
void ADronePawnCom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//////////////AUXILIARY FUNCTIONS//////////////////////

void ADronePawnCom::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    UE_LOG(LogTemp, Warning, TEXT("Entrando en el end play"));
    end();
    dlclose(handle);
    UE_LOG(LogTemp, Warning, TEXT("EndPlay completado"));
}

void ADronePawnCom::setComponents()
{
    //setup rootcomponent
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    //Setup StaticMeshComponent
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DronMesh"));
    MeshComponent->SetupAttachment(RootComponent);


    //section for configuring the spring arm and camera attached to it
    arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    arm->SetupAttachment(RootComponent);

    camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    camera->SetupAttachment(arm,USpringArmComponent::SocketName);
}

void ADronePawnCom::dlImport()
{
    //Here i'll set the call to the dinamic library created for the ros2 comunication
	//And all the functions neccesary in order to set up the functioning listener
	handle = dlopen("/home/daniel/ros2_ws/build/droneCom/liblistenerlib.so", RTLD_LAZY);

	if (!handle)
    {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return;
    }

    //Once the library is open, we take the finctions we want to use, in this case, start, update and end

    void* temp1 = dlsym(handle, "start");
    start = (fun_start)temp1;

    if (!start)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        UE_LOG(LogTemp, Error, TEXT("Error a la hora de cargar start"));
        return;
    }else{
        UE_LOG(LogTemp, Warning, TEXT("Start importado"));
    }

    void* temp2 = dlsym(handle, "update");
    update = (fun_update)temp2;

    if (!update)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        UE_LOG(LogTemp, Error, TEXT("Error a la hora de cargar update"));
        return;
    }else{
        UE_LOG(LogTemp, Warning, TEXT("Update importado"));
    }

    void* temp3 = dlsym(handle, "end");
    end = (fun_end)temp3;

    if (!end)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        UE_LOG(LogTemp, Error, TEXT("Error a la hora de cargar end"));
        return;
    }else{
        UE_LOG(LogTemp, Warning, TEXT("End importado"));
    }
}

void ADronePawnCom::move(FVector pos1)
{
    StartRelLocation = GetActorLocation();
	//We compute the normalized movement
	MoveOffsetNorm = pos1;
	MoveOffsetNorm.Normalize();
    SetActorLocation(StartRelLocation + MoveOffsetNorm);
}