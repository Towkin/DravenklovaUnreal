// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DAttributes.h"

UDAttributes::UDAttributes(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Attributes constructor"));
	m_MaxHealth = 20.0;
}

UDAttributes::~UDAttributes()
{
}


/* Perception-gets */
const float UDAttributes::getViewDistance()
{
	return m_ViewDistance;
}

const float UDAttributes::getDarknessVisionDistance()
{
	return m_DarknessVisionDistance;
}

const float UDAttributes::getListenDistance()
{
	return m_ListenDistance;
}

/* Health-gets */

const float UDAttributes::getMaxHealth()
{
	return m_MaxHealth;
}

const float UDAttributes::getHealth()
{
	return m_Health;
}

const float UDAttributes::getHealthReg()
{
	return m_HealthReg;
}

const float UDAttributes::getHealthDelayTime()
{
	return m_HealthDelayTime;
}

/* Health-sets */
void UDAttributes::setMaxHealth(float a_MaxHealth)
{
	m_MaxHealth = a_MaxHealth;
}

void UDAttributes::setHealth(float a_Health)
{
	m_Health = a_Health;
}

void UDAttributes::setHealthReg(float a_HealthReg)
{
	m_HealthReg = a_HealthReg;
}

void UDAttributes::setHeathDelayTime(float a_HealthDelayTime)
{
	m_HealthDelayTime = a_HealthDelayTime;
}

//Movement-gets

const float UDAttributes::getBaseSpeed()
{
	return m_BaseSpeed;
}

const float UDAttributes::getWalkSpeedMod()
{
	return m_WalkSpeedMod;
}

const float UDAttributes::getSprintingSpeedMod()
{
	return m_SprintingSpeedMod;
}

const float UDAttributes::getCrouchSpeedMod()
{
	return m_CrouchSpeedMod;
}

const float UDAttributes::getJumpForce()
{
	return m_JumpForce;
}

const float UDAttributes::getJumpAirMod()
{
	return m_JumpAirMod;
}

const float UDAttributes::getSprintingTime()
{
	return m_SprintingTime;
}

const float UDAttributes::getSprintingRechargeTime()
{
	return m_SprintingRechargeTime;
}
// Movement-sets
void UDAttributes::setBaseSpeed(float a_BaseSpeed)
{
	m_BaseSpeed = a_BaseSpeed;
}

void UDAttributes::setWalkSpeedMod(float a_WalkSpeedMod)
{
	m_WalkSpeedMod = a_WalkSpeedMod;
}

void UDAttributes::setSprintingSpeedMod(float a_SprintingSpeedMod)
{
	m_SprintingSpeedMod = a_SprintingSpeedMod;
}

void UDAttributes::setCrouchSpeedMod(float a_CrouchSpeedMod)
{
	m_CrouchSpeedMod = a_CrouchSpeedMod;
}

void UDAttributes::setJumpForce(float a_JumpForce)
{
	m_JumpForce = a_JumpForce;
}

void UDAttributes::setJumpAirMod(float a_JumpAirMod)
{
	m_JumpAirMod = a_JumpAirMod;
}

void UDAttributes::setSprintingTime(float a_SprintingTime)
{
	m_SprintingTime = a_SprintingTime;
}

void UDAttributes::setSprintingRechargeTime(float a_SprintingRechargeTime)
{
	m_SprintingRechargeTime = a_SprintingRechargeTime;
}
