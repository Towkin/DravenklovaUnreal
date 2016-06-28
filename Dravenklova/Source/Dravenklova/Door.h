// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DObject.h"
#include "Door.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADoor : public ADObject
{
	GENERATED_BODY()

	virtual void Interact(ADCharacter* pawn) override;
	
	
};
