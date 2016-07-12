// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DObject.h"
#include "DEquipment.generated.h"

/**
 * 
 */
class ADCharacter;

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	Primary,
	Secondary,
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

	void UnequipPrimary(ADCharacter* pawn);

	void UnequipSecondary(ADCharacter* pawn);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	EEquipmentSlot m_Slot;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
		void ReceiveEquip(ADCharacter* User, EEquipmentSlot a_Slot);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
		void ReceiveUnequipPrimary(ADCharacter* User);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
		void ReceiveUnequipSecondary(ADCharacter* User);
};


