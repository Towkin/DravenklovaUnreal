// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DEquipment.h"
#include "DCharacter.h"



void ADEquipment::Equip(ADCharacter* pawn)
{
	ReceiveEquipped(pawn);
	pawn->SetEquipment(this);
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

