// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DPawn.h"
#include "DCharacter.generated.h"
/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADCharacter : public ADPawn
{
	GENERATED_BODY()
public:
	ADCharacter();
	~ADCharacter();
	virtual void MoveForward(float a_Value) override;
protected:


};
