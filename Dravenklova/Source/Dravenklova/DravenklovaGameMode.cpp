// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DravenklovaGameMode.h"
#include "DCharacter.h"

ADravenklovaGameMode::ADravenklovaGameMode()
	: Super()
{
	// Set default pawn class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dravenklova/BP_HalfVampire"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	UE_LOG(LogTemp, Warning, TEXT("Default pawning"));
}


