// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DAttributes.h"

UDAttributes::UDAttributes(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Attributes constructor"));
	
	TArray<EHumors> BlackOnly;	BlackOnly.Init(EHumors::Black,		1);
	TArray<EHumors> YellowOnly;	YellowOnly.Init(EHumors::Yellow,	1);
	TArray<EHumors> RedOnly;	RedOnly.Init(EHumors::Red,			1);
	TArray<EHumors> WhiteOnly;	WhiteOnly.Init(EHumors::White,		1);
	
	m_ViewDistance =			FAttribute(30.f,	50.f,	BlackOnly);
	m_DarknessVisionDistance =	FAttribute(5.f,		50.f,	BlackOnly);
	m_ListenDistance =			FAttribute(20.f,	60.f,	BlackOnly);
	m_MaxHealth =				FAttribute(5.f,		10.f,	RedOnly);
	m_Health =					FAttribute(5.f,		10.f,	RedOnly);
	m_HealthRegenTime =			FAttribute(10.f,	20.f,	RedOnly);
	m_HealthDelayTime =			FAttribute(2.f,		10.f,	RedOnly);
	m_BaseSpeed =				FAttribute(200.f,	600.f,	WhiteOnly);
	m_WalkSpeedMod =			FAttribute(0.0f,	1.f,	YellowOnly);
	m_SprintingSpeedMod =		FAttribute(0.0f,	1.f,	YellowOnly);
	m_CrouchSpeedMod =			FAttribute(0.0f,	1.f,	YellowOnly);
	m_JumpAirMod =				FAttribute(0.0f,	1.f,	YellowOnly);
	m_SprintingTime =			FAttribute(3.f,		15.f,	YellowOnly);
	m_SprintingRechargeTime =	FAttribute(2.f,		8.f,	YellowOnly);
	m_AccuracyMod =				FAttribute(2.f,		8.f,	BlackOnly);
	m_ReloadMod =				FAttribute(2.f,		8.f,	WhiteOnly);
	m_MeleeDamageMod =			FAttribute(2.f,		8.f,	YellowOnly);
	m_MeleeTimeMod =			FAttribute(2.f,		8.f,	WhiteOnly);
}

UDAttributes::~UDAttributes()
{
}


/* Perception-gets */
const float UDAttributes::getViewDistance()
{
	return m_ViewDistance.GetCurrentValue();
}

const float UDAttributes::getDarknessVisionDistance()
{
	return m_DarknessVisionDistance.GetCurrentValue();
}

const float UDAttributes::getListenDistance()
{
	return m_ListenDistance.GetCurrentValue();
}

/* Health-gets */

const float UDAttributes::getMaxHealth()
{
	return m_MaxHealth.GetCurrentValue();
}

const float UDAttributes::getHealth()
{
	return m_Health.GetCurrentValue();
}

const float UDAttributes::getHealthReg()
{
	return m_HealthRegenTime.GetCurrentValue();
}

const float UDAttributes::getHealthDelayTime()
{
	return m_HealthDelayTime.GetCurrentValue();
}


//Movement-gets

const float UDAttributes::getBaseSpeed()
{
	return m_BaseSpeed.GetCurrentValue();
}

const float UDAttributes::getWalkSpeedMod()
{
	return m_WalkSpeedMod.GetCurrentValue();
}
const float UDAttributes::getWalkSpeedFactor()
{
	return m_WalkSpeedMod.GetCurrentValue() + 1.f;
}
//
const float UDAttributes::getSprintingSpeedMod()
{
	return m_SprintingSpeedMod.GetCurrentValue();
}
const float UDAttributes::getSprintingSpeedFactor()
{
	return m_SprintingSpeedMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getCrouchSpeedMod()
{
	return m_CrouchSpeedMod.GetCurrentValue();
}
const float UDAttributes::getCrouchSpeedFactor()
{
	return m_CrouchSpeedMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getJumpForce()
{
	return m_JumpForce.GetCurrentValue();
}

const float UDAttributes::getJumpAirMod()
{
	return m_JumpAirMod.GetCurrentValue();
}
const float UDAttributes::getJumpAirFactor()
{
	return m_JumpAirMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getSprintingTime()
{
	return m_SprintingTime.GetCurrentValue();
}

const float UDAttributes::getSprintingRechargeTime()
{
	return m_SprintingRechargeTime.GetCurrentValue();
}

// Weapon-gets


const float UDAttributes::getAccuracyMod()
{
	return m_AccuracyMod.GetCurrentValue();
}

const float UDAttributes::getReloadMod()
{
	return m_ReloadMod.GetCurrentValue();
}

const float UDAttributes::getMeleeDamageMod()
{
	return m_MeleeDamageMod.GetCurrentValue();
}
const float UDAttributes::getMeleeTimeMod()
{
	return m_MeleeTimeMod.GetCurrentValue();
}

// Humors-gets

const float UDAttributes::getHumorBlack()
{
	return m_HumorBlack;
}

const float UDAttributes::getHumorYellow()
{
	return m_HumorYellow;

}

const float UDAttributes::getHumorRed()
{
	return m_HumorRed;
}

const float UDAttributes::getHumorWhite()
{
	return m_HumorWhite;
}




// Character size sets
void UDAttributes::setCharacterHeight(float a_CharacterHeight)
{
	m_CharacterHeight = a_CharacterHeight;
}

void UDAttributes::setCharacterCrouchHeight(float a_CharacterCrouchHeight)
{
	m_CharacterCrouchHeight = a_CharacterCrouchHeight;
}
void UDAttributes::setCharacterRadius(float a_CharacterRadius)
{
	m_CharacterRadius = a_CharacterRadius;
}

// Character size gets

const float UDAttributes::getCharacterHeight()
{
	return m_CharacterHeight;
}

const float UDAttributes::getCharacterCrouchHeight()
{
	return m_CharacterCrouchHeight;
}

const float UDAttributes::getCharacterRadius()
{
	return m_CharacterRadius;
}
