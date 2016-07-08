// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "FAttribute.h"
#include "DAttributes.generated.h"




/**
 * 
 */
//UCLASS( meta = (ShowOnlyInnerProperties))
UCLASS()
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


	// Weapon gets

	UFUNCTION(BlueprintCallable, Category = "Attributes/Weapon")
		const float getAccuracyMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Weapon")
		const float getReloadMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Weapon")
		const float getMeleeDamageMod();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Weapon")
		const float getMeleeTimeMod();



	// Humor gets
	UFUNCTION(BlueprintCallable, Category = "Attributes/Humors")
		const float getHumorBlack();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Humors")
		const float getHumorYellow();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Humors")
		const float getHumorRed();
	UFUNCTION(BlueprintCallable, Category = "Attributes/Humors")
		const float getHumorWhite();

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
		FAttribute m_ViewDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		FAttribute m_DarknessVisionDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		FAttribute m_ListenDistance;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		FAttribute m_Visibility;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Perception")
		FAttribute m_VisiblityMod;



	/* Visiblity how well the character can be seen by others. This is a number continuously recalculated, /*
	/*	using lightning and other factors, used by NPCs to determine if they see the character.)*/
	// float m_Visiblity

	/* Modifer in the Visibility calculation */
	// float m_VisiblityModifier

	// Health
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Attributes|Health")
		FAttribute m_MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		FAttribute m_Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		FAttribute m_HealthRegenTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Health")
		FAttribute m_HealthDelayTime;

	// Movement

	/* Base value for all movement related speeds*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_BaseSpeed;
	/* Modifer to base-speed when the character walks (Unnecessary)?*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_WalkSpeedMod;
	/* Modifier to base speed when the charcter is sprinting*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_SprintingSpeedMod;
	/* Modifier to base speed when the character is crouching*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_CrouchSpeedMod;
	/* Upwards force to apply while jumping*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_JumpForce;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_JumpAirMod;
	/*Time it takes before the character is fatigued.(linear)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_SprintingTime;
	/* Time it takes to go from 0 to full(linear)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Movement")
		FAttribute m_SprintingRechargeTime;
	
	
	/* Weapon*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Weapon")
		FAttribute m_AccuracyMod;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Weapon")
		FAttribute m_ReloadMod;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Weapon")
		FAttribute m_MeleeDamageMod;
	// Modifies the melle cooldown time 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Weapon")
		FAttribute m_MeleeTimeMod;
	//A modifier to the modifier, Allows heavy weapons to slow characters down,
	//but lets strong character negate the slowness modifier
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Weapon")
		FAttribute m_MoveSpeedModModifier;

	/* Humors*/

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Humors")
		float m_HumorBlack = 0.25f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Humors")
		float m_HumorYellow = 0.25f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Humors")
		float m_HumorRed = 0.25f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes|Humors")
		float m_HumorWhite = 0.25f;



private:
	
};
