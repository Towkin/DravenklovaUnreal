// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DEquipment.h"
#include "DWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADWeapon : public ADEquipment
{
	GENERATED_BODY()

	void BeginPrimaryAction();
	void EndPrimaryAction();
	void BeginSecondaryAction();
	void EndSecondaryAction();
	void BeginReloadAction();
	void EndReloadAction();
	
	
	
};
