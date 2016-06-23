// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DAttributes.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API UDAttributes : public UObject
{
public:

	GENERATED_BODY()

	UDAttributes();
	~UDAttributes();

	// Perception-gets
	UFUNCTION(BlueprintCallable, Category = "Attributes/Perception") 
		const float getViewDistance();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Perception") 
		const float getDarknessVisionDistance();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Perception") 
		const float getListenDistance();


	// Visiblity get/setters
	/* */

	//Health-gets
	UFUNCTION(BlueprintCallable, Category = "Attributes/Health") 
		const float getMaxHealth();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Health") 
		const float getHealth();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Health") 
		const float getHealthReg();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Health") 
		const float getHealthDelayTime();

	// Health-sets
	void setMaxHealth(float a_MaxHealth);
	void setHealth(float a_Health);
	void setHealthReg(float a_HealthReg);
	void setHeathDelayTime(float a_HealthDelayTime);


	// Movement-gets
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getBaseSpeed();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getWalkSpeedMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getSprintingSpeedMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getCrouchSpeedMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getJumpForce();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getJumpAirMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getSprintingTime();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getSprintingRechargeTime();

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
