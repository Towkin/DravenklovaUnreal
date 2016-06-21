// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DravenklovaGameMode.h"
#include "DPawn.h"
#include "DPController.h"
#include "HalfVampire.h"

ADravenklovaGameMode::ADravenklovaGameMode()
{
	
	static ConstructorHelpers::FClassFinder<AHalfVampire> PlayerPawnClassFinder(TEXT("/Game/Dravenklova/Blueprints/BP_HalfVampire"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = ADPController::StaticClass();

	UE_LOG(LogTemp, Warning, TEXT("Default pawning"));
}


