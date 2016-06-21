// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DPController.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADPController : public APlayerController
{
	GENERATED_BODY()
public: 
	ADPController();
	
protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface		

	virtual void MoveForward(float a_Value);

	/** Navigate player to the given world location. */
	//void SetNewMoveDestination(const FVector DestLocation);
	
	
};
