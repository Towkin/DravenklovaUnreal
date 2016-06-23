// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class DRAVENKLOVA_API DAttributes
{
public:

	DAttributes();
	~DAttributes();
	// Perception-gets
	float getViewDistance(float a_ViewDis);
	float getDarknessVisionDistance(float a_DarknessVisDis);
	float getListenDistance(float a_LisDis);


	// Visiblity get/setters
	/* */

	//Health-gets
	float getMaxHealth(float a_MaxHealth);
	float getHealth(float a_Health);
	float getHealthReg(float a_HealthReg);
	float getHealthDelayTime(float a_HealthDelayTime);

	// Health-sets
	void setMaxHealth(float a_MaxHealth);
	void setHealth(float a_Health);
	void setHealthReg(float a_HealthReg);
	void setHeathDelayTime(float a_HealthDelayTime);


	// Movement-gets
	float getBaseSpeed(float m_BaseSpeed);
	float getWalkSpeedMod(float a_WalkSpeedMod);
	float getSprintingSpeedMod(float a_SprintingSpeedMod);
	float getCrouchSpeedMod(float a_CrouchSpeedMod);
	float getJumpForce(float a_JumpForce);
	float getJumpAirMod(float a_JumpAirMod);
	float getSprintingTime(float a_SprintingTime);
	float getSprintingRechargeTime(float a_SprintingRechargeTime);

	// Movement-sets
	void setBaseSpeed(float a_BaseSpeed);
	void setWalkSpeedMod(float a_WalkSpeedMod);
	void setSprintingSpeedMod(float a_SprintingSpeedMod);
	void setCrouchSpeedMod(float a_CrouchSpeedMod);
	void setJumpForce(float a_JumpForce);
	void setJumpAirMod(float a_JumpAirMod);
	void setSprintingTime(float a_SprintingTime);
	void setSprintingRechargeTime(float a_SprintingRechargeTime);

	
protected:

private:
	// General

	bool b_IsAlive;
	bool b_IsEnemy;

	// Perception
	float m_ViewDistance;
	float m_DarknessVisionDistance;
	float m_ListenDistance;

	/* Visiblity how well the character can be seen by others. This is a number continuously recalculated, /*
	/*	using lightning and other factors, used by NPCs to determine if they see the character.)*/
	// float m_Visiblity

	/* Modifer in the Visibility calculation */
	// float m_VisiblityModifier

	// Health
	float m_MaxHealth;
	float m_Health;

	float m_HealthReg;
	float m_HealthDelayTime;

	// Movement

	/* Base value for all movement related speeds*/
	float m_BaseSpeed;
	/* Modifer to base-speed when the character walks (Unnecessary)?*/
	float m_WalkSpeedMod;
	/* Modifier to base speed when the charcter is sprinting*/
	float m_SprintingSpeedMod;
	/* Modifier to base speed when the character is crouching*/
	float m_CrouchSpeedMod;
	/* Upwards force to apply while jumping*/
	float m_JumpForce;

	float m_JumpAirMod;
	/*Time it takes before the character is fatigued.(linear)*/
	float m_SprintingTime;
	/* Time it takes to go from 0 to full(linear)*/
	float m_SprintingRechargeTime;

	/* Weapon Attributes */

	/* All */

	/*Melee*/

	/* Ranged */


	/* Humorism */
	
};
