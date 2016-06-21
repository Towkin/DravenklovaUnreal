// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DPawn.h"
#include "HalfVampire.generated.h"
/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API AHalfVampire : public ADPawn
{
	GENERATED_BODY()
public:

	virtual void MoveForward(float a_Value);
	AHalfVampire();
	~AHalfVampire();
};
