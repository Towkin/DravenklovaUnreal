// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DObject.h"
#include "DEquipment.generated.h"

/**
 * 
 */
class ADCharacter;

UCLASS()
class DRAVENKLOVA_API ADEquipment : public ADObject
{
	GENERATED_BODY()
public:
	virtual void Interact(ADCharacter* pawn) override;

	virtual void EndInteract(ADCharacter* pawn) override;
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	virtual void Equip(ADCharacter* pawn);
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void Unequip(ADCharacter* pawn);


	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void ReceiveEquipped(ADCharacter* User);

	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void ReceiveUnequipped(ADCharacter* User);
};



