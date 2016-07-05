// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DAttributes.generated.h"

/**
 * 
 */
//UCLASS( meta = (ShowOnlyInnerProperties))
UCLASS(/*meta = (BlueprintSpawnableComponent)*/)
class DRAVENKLOVA_API UDAttributes : public UActorComponent
{

	GENERATED_UCLASS_BODY()

public:


	/* Character sizes  */

	//UDAttributes(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
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
		const float getWalkSpeedFactor();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getSprintingSpeedMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getSprintingSpeedFactor();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getCrouchSpeedMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getCrouchSpeedFactor();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement") 
		const float getJumpForce();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getJumpAirMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Movement")
		const float getJumpAirFactor();
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

	// Character sizes

	void setCharacterHeight(float a_CharacterHeight);
	void setCharacterCrouchHeight(float a_CharacterCrouchHeight);
	void setCharacterRadius(float a_CharacterRadius);

	UFUNCTION(BlueprintCallable, Category = "Attributes|Size")
		const float getCharacterHeight();
	UFUNCTION(BlueprintCallable, Category = "Attributes|Size")
		const float getCharacterCrouchHeight();
	UFUNCTION(BlueprintCallable, Category = "Attributes|Size")
		const float getCharacterRadius();

	bool b_IsCrouching = false;
	bool b_IsSprinting = false;

protected:

	// General

	bool b_IsAlive;
	bool b_IsEnemy;

	// Character sizes
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Size")
		float m_CharacterHeight = 180.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Size")
		float m_CharacterCrouchHeight = 90.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Size")
		float m_CharacterRadius = 35.f;


	// Perception
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		float m_ViewDistance = 20.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		float m_DarknessVisionDistance = 5.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		float m_ListenDistance = 30.f;

	/* Visiblity how well the character can be seen by others. This is a number continuously recalculated, /*
	/*	using lightning and other factors, used by NPCs to determine if they see the character.)*/
	// float m_Visiblity

	/* Modifer in the Visibility calculation */
	// float m_VisiblityModifier

	// Health
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Attributes|Health")
		float m_MaxHealth = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		float m_Health = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		float m_HealthRegenTme = 10.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		float m_HealthDelayTime = 5.f;

	// Movement

	/* Base value for all movement related speeds*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_BaseSpeed = 200;
	/* Modifer to base-speed when the character walks (Unnecessary)?*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_WalkSpeedMod = 0.f;
	/* Modifier to base speed when the charcter is sprinting*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_SprintingSpeedMod = 1.5f;
	/* Modifier to base speed when the character is crouching*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_CrouchSpeedMod = -0.5f;
	/* Upwards force to apply while jumping*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_JumpForce = 250.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_JumpAirMod = -0.75f;
	/*Time it takes before the character is fatigued.(linear)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_SprintingTime = 8.f;
	/* Time it takes to go from 0 to full(linear)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		float m_SprintingRechargeTime = 10.f;

	/* Weapon Attributes */

	/* All */

	/*Melee*/

	/* Ranged */


	/* Humorism */

private:
	
};
