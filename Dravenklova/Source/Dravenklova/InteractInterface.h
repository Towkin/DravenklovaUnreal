// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "InteractInterface.generated.h"

class ADCharacter;

UINTERFACE(MinimalAPI)
class UInteractInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()	
};

class IInteractInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual void Interact(ADCharacter* pawn);
};
