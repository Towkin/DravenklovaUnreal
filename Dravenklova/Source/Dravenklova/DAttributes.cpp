// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DAttributes.h"

DAttributes::DAttributes()
{
}

DAttributes::~DAttributes()
{
}


/* Perception-gets */
float DAttributes::getViewDistance(float a_ViewDis)
{
	return m_ViewDistance;
}

float DAttributes::getDarknessVisionDistance(float a_DarknessVisDis)
{
	return m_DarknessVisionDistance;
}

float DAttributes::getListenDistance(float a_LisDis)
{
	return m_ListenDistance;
}

/* Health-gets */

float DAttributes::getMaxHealth(float a_MaxHealth)
{
	return m_MaxHealth;
}

float DAttributes::getHealth(float a_Health)
{
	return m_Health;
}

float DAttributes::getHealthReg(float a_HealthReg)
{
	return m_HealthReg;
}

float DAttributes::getHealthDelayTime(float a_HealthDTime)
{
	return m_HealthDelayTime;
}

/* Health-sets */
void DAttributes::setMaxHealth(float a_MaxHealth)
{
	m_MaxHealth = a_MaxHealth;
}

void DAttributes::setHealth(float a_Health)
{
	m_Health = a_Health;
}

void DAttributes::setHealthReg(float a_HealthReg)
{
	m_HealthReg = a_HealthReg;
}

void DAttributes::setHeathDelayTime(float a_HealthDelayTime)
{
	m_HealthDelayTime = a_HealthDelayTime;
}

//Movement-gets

float DAttributes::getBaseSpeed(float m_BaseSpeed)
{
	return 0.0f;
}

float DAttributes::getWalkSpeedMod(float a_WalkSpeedMod)
{
	return m_WalkSpeedMod;
}

float DAttributes::getSprintingSpeedMod(float a_SprintingSpeedMod)
{
	return m_SprintingSpeedMod;
}

float DAttributes::getCrouchSpeedMod(float a_CrouchSpeedMod)
{
	return m_CrouchSpeedMod;
}

float DAttributes::getJumpForce(float a_JumpForce)
{
	return m_JumpForce;
}

float DAttributes::getJumpAirMod(float a_JumpAirMod)
{
	return m_JumpAirMod;
}

float DAttributes::getSprintingTime(float a_SprintingTime)
{
	return m_SprintingTime;
}

float DAttributes::getSprintingRechargeTime(float a_SprintingRechargeTime)
{
	return m_SprintingRechargeTime;
}
// Movement-sets
void DAttributes::setBaseSpeed(float a_BaseSpeed)
{
	m_BaseSpeed = a_BaseSpeed;
}

void DAttributes::setWalkSpeedMod(float a_WalkSpeedMod)
{
	m_WalkSpeedMod = a_WalkSpeedMod;
}

void DAttributes::setSprintingSpeedMod(float a_SprintingSpeedMod)
{
	m_SprintingSpeedMod = a_SprintingSpeedMod;
}

void DAttributes::setCrouchSpeedMod(float a_CrouchSpeedMod)
{
	m_CrouchSpeedMod = a_CrouchSpeedMod;
}

void DAttributes::setJumpForce(float a_JumpForce)
{
	m_JumpForce = a_JumpForce;
}

void DAttributes::setJumpAirMod(float a_JumpAirMod)
{
	m_JumpAirMod = a_JumpAirMod;
}

void DAttributes::setSprintingTime(float a_SprintingTime)
{
	m_SprintingTime = a_SprintingTime;
}

void DAttributes::setSprintingRechargeTime(float a_SprintingRechargeTime)
{
	m_SprintingRechargeTime = a_SprintingRechargeTime;
}
