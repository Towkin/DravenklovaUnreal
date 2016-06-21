// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DPController.h"
#include "DPawn.h"


ADPController::ADPController()
{
	
}

void ADPController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ADPController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Bind input to movement methods
	InputComponent->BindAxis("MoveForward", this, &ADPController::MoveForward);
	UE_LOG(LogTemp, Warning, TEXT("Binding input"));
}

void ADPController::MoveForward(float a_Value)
{
	if (a_Value != 0.0f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Move forward?"));
		ADPawn* const pawn = (ADPawn*) GetPawn();

		// This should not be done here? - different pawns have different movement attributes
		//FVector MyDest = FVector(pawn->GetActorLocation() + FVector(120, 0, 0) * a_Value);

		pawn->MoveForward(a_Value);
		//SetNewMoveDestination(MyDest);
	}
}

