// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FAttribute.generated.h"

/**
 * 
 */

class UDAttributes;

UENUM(BlueprintType) 
enum class EHumors : uint8
{
	Black  UMETA(DisplayName="Black"),
	Yellow UMETA(DisplayName = "Yellow"), 
	Red UMETA(DisplayName = "Red"),
	White UMETA(DisplayName = "White")
};

USTRUCT(BlueprintType)
struct FAttribute
{
	GENERATED_USTRUCT_BODY()

	void UpdateAttribute(UDAttributes* Attributes);
	
	float GetCurrentValue() const;

	FAttribute(float A = 0.0f, float B = 1.0f, const TArray<EHumors>& Humors = TArray<EHumors>());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
		float m_Value0 = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
		float m_Value1 = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attribute)
		TArray<EHumors> m_StatTypes;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attribute)
		float m_CurrentValue;
};
