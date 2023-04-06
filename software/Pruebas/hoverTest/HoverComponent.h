// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HoverComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HOVERTEST_API UHoverComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHoverComponent();

	//Funcion para poder setear el hover con una tecla
	void InputHover(UInputComponent* PlayerInputComponent);

	//Funcion para hacer true el hover
	void SetHover();

	//Funcion Hover
	void Hover(float DeltaTime);

	//Funcion para volver a la posicion de inicio
	void ResetPosition();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Toggle para saber si iniciar el hover o no
	UPROPERTY(EditAnywhere)
	bool TriggerHover = true;

	//Toggle para saber si resetear el hover
	UPROPERTY(EditAnywhere)
	bool Reset = true;

	//Altura en la que queremos el dron
	UPROPERTY(EditAnywhere)
	float Height = 500.0f;

	//Velocidad a la que queremos que se mueva
	UPROPERTY(EditAnywhere)
	float Speed = 120.0f;

	//Ubicaciones computadas o a computar
	FVector StartRelativeLocation;
	FVector HeightNorm;					//Variable para normalizar el vector d ela posicion final y poder mover el dron de "poco en poco"
	float MaxHeight = 0.0f;
	float ActualHeight = 0.0f;
	
};