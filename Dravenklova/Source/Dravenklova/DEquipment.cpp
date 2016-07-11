// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DEquipment.h"
#include "DCharacter.h"



void ADEquipment::Equip(ADCharacter* pawn)
{
	switch (m_Slot)
	{
	case Primary:
		if (!pawn->GetPrimary())
		{
			pawn->SetPrimary(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Primary is Occupied"));
		}
		break;
	case Secondary:
		if (!SecondaryIsOccupied(pawn))
		{
			SetAsSecondary(pawn);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Secondary is Occupied"));
		}

		break;
	case Arrow:
		AddArrows(pawn);
		break;

	case Sampler:
		SetSampler(pawn);
		break;

	default:
		break;
	}


	UE_LOG(LogTemp, Warning, TEXT("Equip"));
}


void ADEquipment::Unequip(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Unequip"));

}

 void ADEquipment::Interact(ADCharacter* pawn)
{
	Equip(pawn);
}
void ADEquipment::EndInteract(ADCharacter* pawn)
{
	
}

void ADEquipment::SetSampler(ADCharacter* pawn)
{

}

void ADEquipment::AddArrows(ADCharacter* pawn)
{

}