// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "InteractInterface.h"
#include "DCharacter.h"

UInteractInterface::UInteractInterface(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void IInteractInterface::Interact(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Base function for Interact"));
}
void IInteractInterface::EndInteract(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Base function for End Interact"));
}