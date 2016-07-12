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


	float m_CharacterMoveSpeedMod;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
		const float getCharacterMoveSpeedMod();

	void PrimaryActionBegin();
	void PrimaryActionEnd();
	void SecondaryActionBegin();
	void SecondaryActionEnd();
	void ReloadActionBegin();
	void ReloadActionEnd();
	
	
	
};
