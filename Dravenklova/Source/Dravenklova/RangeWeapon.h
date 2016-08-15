// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DWeapon.h"
#include "RangeWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ARangeWeapon : public ADWeapon
{
	GENERATED_BODY()
public:
	ARangeWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	// Arbitary number representing likeihood to it where aimied. Higher means more likely.
	float m_Accuracy;
	float m_ReloadTime;
	float m_FireCooldownTime;


	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getAccuracy() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getReloadTime() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getFireCooldownTime() const;



	
	
	
};
