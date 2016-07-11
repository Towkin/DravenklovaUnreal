// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DObject.h"
#include "DEquipment.generated.h"

/**
 * 
 */

UENUM()
enum EquipmentSlot
{
	Primary,
	Secondary,
	Arrow,
	Sampler
};

UCLASS()
class DRAVENKLOVA_API ADEquipment : public ADObject
{
	GENERATED_BODY()
public:



	virtual void Interact(ADCharacter* pawn) override;
	
	virtual void EndInteract(ADCharacter* pawn) override;
	
	void Equip(ADCharacter* pawn);

	void Unequip(ADCharacter* pawn);

	EquipmentSlot m_Slot;

	void SetSampler(ADCharacter* pawn);
	
	void AddArrows(ADCharacter* pawn);
	
	
	
};


