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
protected:
	// Arbitary number representing likelyhood to it where aimied. Higher means more likely.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Range")
	float m_Accuracy = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Range")
	float m_ReloadTime = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon|Range")
	float m_FireCooldownTime = 0.f;

public:
	// Getters
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getAccuracy() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getReloadTime() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon|Range")
	const float getFireCooldownTime() const;



	
	
	
};
