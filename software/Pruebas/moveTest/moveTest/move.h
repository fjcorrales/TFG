// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "move.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMoveReachEndPointSignature, bool, IsTopEndpoint);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MOVETEST_API Umove : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Umove();

	UFUNCTION(BlueprintCallable)
	void EnableMovement(bool shouldMove);

	UFUNCTION(BlueprintCallable)
	void ResetMovement();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:

	//Offset to move
	UPROPERTY(EditAnywhere)
	FVector MoveOffset;

	//Speed
	UPROPERTY(EditAnywhere)
	float Speed = 1.0f;

	//Enable the movement of the component
	UPROPERTY(EditAnywhere)
	bool MoveEnable = true;
	
	//On extreme reached event
	UPROPERTY(BlueprintAssignable)
	FOnMoveReachEndPointSignature OnEndpointReached;

	//Computed locations
	FVector StartRelativeLocation;
	FVector MoveOffsetNorm;
	float MaxDistance = 0.0f;
	float CurDistance = 0.0f;
	int MoveDirection = 1;
	
};
