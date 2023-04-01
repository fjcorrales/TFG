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

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Height
	UPROPERTY(EditAnywhere)
	float Height = 1.0f;

	//Speed
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	//Ubicaciones computadas 
	FVector StartRelLocation;
	FVector MoveOffsetNorm;
	int MoveDirection = 1;
	int MaxHeight = 0;
	float CurDistance = 0.0f;
	float MaxDistance = 0.0f;

	//Offset para moverse
	FVector MoveOffset;

	
};
