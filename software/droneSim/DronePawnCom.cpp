// Fill out your copyright notice in the Description page of Project Settings.


#include "DronePawnCom.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


// Sets default values
ADronePawnCom::ADronePawnCom()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADronePawnCom::BeginPlay()
{

	Super::BeginPlay();
	
	//Here we'll set the call to the dinamic library created for the ros2 comunication
	void *handle;
    int (*start)(int num);
	int (*update)(int num);
	int (*end)(int num);
	handle = dlopen("../ros2_ws/src/droneCom/src/subscriber_member_function.h", RTLD_LAZY);

	if (!handle)
    {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }

    *(void **)(&start) = dlsym(handle, "dummy");

    if (!start)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
	*(void **)(&update) = dlsym(handle, "dummy");

    if (!UpdateComponentTransforms)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
	*(void **)(&end) = dlsym(handle, "dummy");

    if (!end)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
    dlclose(handle);
}

// Called every frame
void ADronePawnCom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADronePawnCom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

