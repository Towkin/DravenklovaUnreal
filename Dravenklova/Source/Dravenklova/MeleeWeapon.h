// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DWeapon.h"
#include "MeleeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API AMeleeWeapon : public ADWeapon
{
	GENERATED_BODY()

		
	
	float m_MeleeDamage;
	float m_MeleeCooldownTime;

	// gets

	UFUNCTION(BlueprintCallable, Category = "Weapon|Melee")
		const float getMeleeDamage();
	UFUNCTION(BlueprintCallable, Category = "Weapon|Melee")
		const float getMeleeCooldownTime();


	
	
};
