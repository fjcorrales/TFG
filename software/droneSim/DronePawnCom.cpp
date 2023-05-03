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

    //void (*start)();
	//void (*update)();
	//int (*end)();
    int (*dummy)(int num);
// Called when the game starts or when spawned
void ADronePawnCom::BeginPlay()
{

	Super::BeginPlay();
	
	//Here we'll set the call to the dinamic library created for the ros2 comunication
	void *handle;
   
    int resultado;
	handle = dlopen("../ros2_ws/src/droneCom/src/subscriber_member_function.h", RTLD_LAZY);

	if (!handle)
    {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    *(void **)(&dummy) = dlsym(handle, "dummy");

    if (!dummy)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
    }

   /* (void **)(&start) = dlsym(handle, "start");

    if (!start)
    {
       // no such symbol 
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
	*(void **)(&update) = dlsym(handle, "update");

    if (!UpdateComponentTransforms)
    {
        // no such symbol 
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
	

    *(void **)(&end) = dlsym(handle, "end");

    if (!end)
    {
        //no such symbol 
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        exit(1);
    }
    
    start();
    //dlclose(handle);
    */
}

// Called every frame
void ADronePawnCom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //update();

}

// Called to bind functionality to input
void ADronePawnCom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

