// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DAttributes.h"
#include "DCharacter.h"

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

	UpdateAttributes();
}

UDAttributes::~UDAttributes()
{
}

void UDAttributes::UpdateAttributes()
{
	m_ViewDistance.UpdateAttribute(this);
	m_DarknessVisionDistance.UpdateAttribute(this);
	m_ListenDistance.UpdateAttribute(this);
	
	m_MaxHealth.UpdateAttribute(this);
	m_Health.UpdateAttribute(this);
	m_HealthRegenTime.UpdateAttribute(this);
	m_HealthDelayTime.UpdateAttribute(this);

	m_BaseSpeed.UpdateAttribute(this);
	m_WalkSpeedMod.UpdateAttribute(this);
	m_SprintingSpeedMod.UpdateAttribute(this);
	m_CrouchSpeedMod.UpdateAttribute(this);
	m_JumpAirMod.UpdateAttribute(this);
	m_SprintingTime.UpdateAttribute(this);
	m_SprintingRechargeTime.UpdateAttribute(this);
	
	m_AccuracyMod.UpdateAttribute(this);
	m_ReloadMod.UpdateAttribute(this);
	m_MeleeDamageMod.UpdateAttribute(this);
	m_MeleeTimeMod.UpdateAttribute(this);
}
/* Perception-gets */
const float UDAttributes::getViewDistance() const
{
	return m_ViewDistance.GetCurrentValue();
}

const float UDAttributes::getDarknessVisionDistance() const
{
	return m_DarknessVisionDistance.GetCurrentValue();
}

const float UDAttributes::getListenDistance() const
{
	return m_ListenDistance.GetCurrentValue();
}

/* Health-gets */

const float UDAttributes::getMaxHealth() const
{
	return m_MaxHealth.GetCurrentValue();
}

const float UDAttributes::getHealth() const
{
	return m_Health.GetCurrentValue();
}

const float UDAttributes::getHealthReg() const
{
	return m_HealthRegenTime.GetCurrentValue();
}

const float UDAttributes::getHealthDelayTime() const
{
	return m_HealthDelayTime.GetCurrentValue();
}


//Movement-gets

const float UDAttributes::getBaseSpeed() const
{
	return m_BaseSpeed.GetCurrentValue();
}

const float UDAttributes::getWalkSpeedMod() const
{
	return m_WalkSpeedMod.GetCurrentValue();
}
const float UDAttributes::getWalkSpeedFactor() const
{
	return m_WalkSpeedMod.GetCurrentValue() + 1.f;
}
//
const float UDAttributes::getSprintingSpeedMod() const 
{
	return m_SprintingSpeedMod.GetCurrentValue();
}
const float UDAttributes::getSprintingSpeedFactor() const
{
	return m_SprintingSpeedMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getCrouchSpeedMod() const
{
	return m_CrouchSpeedMod.GetCurrentValue();
}
const float UDAttributes::getCrouchSpeedFactor() const
{
	return m_CrouchSpeedMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getJumpForce() const
{
	return m_JumpForce.GetCurrentValue();
}

const float UDAttributes::getJumpAirMod() const
{
	return m_JumpAirMod.GetCurrentValue();
}
const float UDAttributes::getJumpAirFactor() const
{
	return m_JumpAirMod.GetCurrentValue() + 1.f;
}

const float UDAttributes::getSprintingTime() const
{
	return m_SprintingTime.GetCurrentValue();
}

const float UDAttributes::getSprintingRechargeTime() const
{
	return m_SprintingRechargeTime.GetCurrentValue();
}


const float UDAttributes::getCurrentMaxSpeed() const
{
	return getBaseSpeed() * 
		((!b_IsSprinting && !b_IsCrouching) ? getWalkSpeedFactor() : 1.f) * 
		(b_IsSprinting ? getSprintingSpeedFactor() : 1.f) * 
		(b_IsCrouching ? getCrouchSpeedFactor() : 1.f);
}

// Weapon-gets


const float UDAttributes::getAccuracyMod() const
{
	return m_AccuracyMod.GetCurrentValue();
}

const float UDAttributes::getReloadMod() const
{
	return m_ReloadMod.GetCurrentValue();
}

const float UDAttributes::getMeleeDamageMod() const
{
	return m_MeleeDamageMod.GetCurrentValue();
}
const float UDAttributes::getMeleeTimeMod() const
{
	return m_MeleeTimeMod.GetCurrentValue();
}

// Humors-gets

const float UDAttributes::getHumorBlack() const
{
	return m_HumorBlack;
}

const float UDAttributes::getHumorYellow() const
{
	return m_HumorYellow;

}

const float UDAttributes::getHumorRed() const
{
	return m_HumorRed;
}

const float UDAttributes::getHumorWhite() const
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

const float UDAttributes::getCharacterHeight() const
{
	return m_CharacterHeight;
}

const float UDAttributes::getCharacterCrouchHeight() const
{
	return m_CharacterCrouchHeight;
}

const float UDAttributes::getCharacterRadius() const
{
	return m_CharacterRadius;
}

const float UDAttributes::getCurrentCharacterHeight() const
{
	return b_IsCrouching ? getCharacterCrouchHeight() : getCharacterHeight();
}
