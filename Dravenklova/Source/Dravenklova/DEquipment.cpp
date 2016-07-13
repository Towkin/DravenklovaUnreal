// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DEquipment.h"
#include "DCharacter.h"



void ADEquipment::Equip(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Equipping..."));

	switch (m_Slot)
	{
	case EEquipmentSlot::Primary:
		if (!pawn->GetPrimary())
		{
			ReceiveEquipped(pawn, m_Slot);
			pawn->SetPrimary(this);
			UE_LOG(LogTemp, Warning, TEXT("Equipped to Primary"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Primary is Occupied"));
		}
		break;
	case EEquipmentSlot::Secondary:
		if (!pawn->GetSecondary())
		{
			ReceiveEquipped(pawn, m_Slot);
			pawn->SetSecondary(this);
			UE_LOG(LogTemp, Warning, TEXT("Equipped to Secondary"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Secondary is Occupied"));
		}

		break;

	case EEquipmentSlot::Sampler:
		ReceiveEquipped(pawn, m_Slot);
		pawn->SetSampler(this);
		break;

	default:
		break;
	}

	
}

void ADEquipment::Unequip(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("Unequipped"));

	ReceiveUnequipped(pawn);
}

//void ADEquipment::UnequipPrimary(ADCharacter* pawn)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Unequip primary"));
//	
//	ReceiveUnequipPrimary(pawn);
//
//}
//void ADEquipment::UnequipSecondary(ADCharacter* pawn)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Unequip secondary"));
//	
//	ReceiveUnequipSecondary(pawn);
//}

 void ADEquipment::Interact(ADCharacter* pawn)
{
	Super::Interact(pawn);

	Equip(pawn);
}

void ADEquipment::EndInteract(ADCharacter* pawn)
{
	Super::EndInteract(pawn);
}

