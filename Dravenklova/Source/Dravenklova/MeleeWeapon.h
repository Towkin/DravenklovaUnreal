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
public:
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	float m_MeleeDamage;
	float m_MeleeCooldownTime;

	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Melee")
	const float getMeleeDamage() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Melee")
	const float getMeleeCooldownTime() const;


	
	
};
