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

ADronePawnCom::~ADronePawnCom()
{
 	dlclose(handle);
    end();
}
// Called when the game starts or when spawned
void ADronePawnCom::BeginPlay()
{

	Super::BeginPlay();
	
	//Here we'll set the call to the dinamic library created for the ros2 comunication
	//And all the functions neccesary in order to set up the functioning listener
   
	handle = dlopen("/home/daniel/ros2_ws/build/droneCom/liblistenerlib.so", RTLD_LAZY);

	if (!handle)
    {
        /* fail to load the library */
        fprintf(stderr, "Error: %s\n", dlerror());
        return;
    }

    void* temp = dlsym(handle, "dummy");
    dummy = (fun_dummy)temp;

    if (!dummy)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
    }else{    
        int aux = dummy(1);
        UE_LOG(LogTemp, Warning, TEXT("%d"),aux);
    }
   
    void* temp1 = dlsym(handle, "start");
    start = (fun_start)temp1;

    if (!start)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return;
    }

    void* temp2 = dlsym(handle, "update");
    update = (fun_update)temp2;

    if (!update)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return;
    }

    void* temp3 = dlsym(handle, "end");
    end = (fun_end)temp3;

    if (!end)
    {
        /* no such symbol */
        fprintf(stderr, "Error: %s\n", dlerror());
        dlclose(handle);
        return;
    }

    //We call the start function to set up the listener
    start();
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

