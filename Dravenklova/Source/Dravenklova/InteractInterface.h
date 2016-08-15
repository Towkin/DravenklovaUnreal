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
public:
	//IInteractInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Interact(ADCharacter* pawn);
	virtual void EndInteract(ADCharacter* pawn);
};
