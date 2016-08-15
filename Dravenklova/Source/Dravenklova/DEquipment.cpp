// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DEquipment.h"
#include "DCharacter.h"


ADEquipment::ADEquipment(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
void ADEquipment::Equip(ADCharacter* pawn)
{
	if (!pawn->GetEquipment())
	{
		ReceiveEquipped(pawn);
		pawn->SetEquipment(this);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Tried to pick up multiple equipment : DEquipment::Equip"))
	}
}

void ADEquipment::Unequip(ADCharacter* pawn)
{
	ReceiveUnequipped(pawn);
}

 void ADEquipment::Interact(ADCharacter* pawn)
{
	Super::Interact(pawn);

	Equip(pawn);
}

void ADEquipment::EndInteract(ADCharacter* pawn)
{
	Super::EndInteract(pawn);
}

