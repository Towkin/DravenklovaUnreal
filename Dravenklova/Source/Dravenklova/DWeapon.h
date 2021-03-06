// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DEquipment.h"
#include "DWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADWeapon : public ADEquipment
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float m_CharacterMoveSpeedMod = 0.f;
public:
	ADWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	const float getCharacterMoveSpeedMod() const;

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	virtual void Equip(ADCharacter* pawn) override;

	void PrimaryActionBegin();
	void PrimaryActionEnd();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnPrimaryActionBegin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnPrimaryActionEnd();

	void SecondaryActionBegin();
	void SecondaryActionEnd();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnSecondaryActionBegin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnSecondaryActionEnd();
	
	void ReloadActionBegin();
	void ReloadActionEnd();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnReloadActionBegin();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnReloadActionEnd();
};