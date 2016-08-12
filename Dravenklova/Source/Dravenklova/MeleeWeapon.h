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
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	float m_MeleeDamage = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Melee")
	float m_MeleeCooldownTime = 0.f;

public:
	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Melee")
	const float getMeleeDamage() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Melee")
	const float getMeleeCooldownTime() const;
};
