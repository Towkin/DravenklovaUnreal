// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DEquipment.h"
#include "DCharacter.h"



void ADEquipment::Equip(ADCharacter* pawn)
{
	switch (m_Slot)
	{
	case EEquipmentSlot::Primary:
		if (!pawn->GetPrimary())
		{
			pawn->SetPrimary(this);
			ReceiveEquip(pawn, m_Slot);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Primary is Occupied"));
		}
		break;
	case EEquipmentSlot::Secondary:
		if (!pawn->GetSecondary())
		{
			pawn->SetSecondary(this);
			ReceiveEquip(pawn, m_Slot);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Secondary is Occupied"));
		}

		break;

	case EEquipmentSlot::Sampler:
		pawn->SetSampler(this);
		ReceiveEquip(pawn, m_Slot);
		break;

	default:
		break;
	}

	UE_LOG(LogTemp, Warning, TEXT("Equip"));
}


void ADEquipment::UnequipPrimary(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Unequip primary"));
	
	ReceiveUnequipPrimary(pawn);

}
void ADEquipment::UnequipSecondary(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Unequip secondary"));
	
	ReceiveUnequipSecondary(pawn);
}

 void ADEquipment::Interact(ADCharacter* pawn)
{
	Equip(pawn);
}

void ADEquipment::EndInteract(ADCharacter* pawn)
{
	
}

