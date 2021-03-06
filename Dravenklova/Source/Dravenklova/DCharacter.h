// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UDAttributes;
class IInteractInterface;
class ADEquipment;
class ADWeapon;

UCLASS()
class DRAVENKLOVA_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UDAttributes* m_Attributes;

	virtual void OnConstruction(const FTransform& Transform) override;
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
		void OnDeath(ADCharacter* DChar);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes|Health")
	virtual float getCurrentHealth() const;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Attributes|Health")
	float getCurrentHealthPercentage() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
	virtual void setCurrentHealth(float a_NewHealth);
	UFUNCTION(BlueprintCallable, Category = "Attributes|Health")
	void setCurrentHealthPercentage(float a_NewHealthPercentage);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;



	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interact")
	void ProvideInteractBegin(AActor* Reciever);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interact")
	void ProvideInteractEnd(AActor* Reciever);

	// Added unique equipment events /E, 16-07-13
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideEquippedWeapon(ADWeapon* weapon);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideUnequippedWeapon(ADWeapon* weapon);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideEquippedEquipment(ADEquipment* equipment);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideUnequippedEquipment(ADEquipment* equipment);

	// Added UFUNCTION calls /E, 16-07-13
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Equipment")
	ADWeapon* GetWeapon() const;
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetWeapon(ADWeapon* weapon);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Equipment")
	ADEquipment* GetEquipment() const;
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetEquipment(ADEquipment* equipment);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void DropWeapon();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void DropEquipment();

	//UFUNCTION(BlueprintCallable, Category = "Equipment")
	//void SetSampler(ADEquipment* a_Sampler);

	// Sets b_NeedsAttributeUpdate to true, which'll make UpdateAttributes() called in the next tick. /E 16-07-21
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void CallUpdateAttributes();

	void MoveForward(float a_Value);
	void MoveRight(float a_Value);

	void Turn(float a_Value);
	void LookUp(float a_Value);
	
	void StartJump();
	void StopJump();

	void EnableSprint();
	void DisableSprint();

	void EnableCrouch();
	void DisableCrouch();

	void EnableCheckStats();
	void DisableCheckStats();

	// Primary Equipment (Weapon) actions /E 16-07-25
	void StartPrimaryAction();
	void StopPrimaryAction();

	void StartSecondaryAction();
	void StopSecondaryAction();

	void StartReloadAction();
	void StopReloadAction();

	UFUNCTION(BlueprintCallable, Category = "Interact")
		void Use();
	UFUNCTION(BlueprintCallable, Category = "Interact")
		void EndUse();

protected:

	float m_HealthPercentage = 1.f;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnStartJump();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnStopJump();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnSprintEnabled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnSprintDisabled();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnCrouchEnabled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnCrouchDisabled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sampler")
	void OnEnableCheckStats();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sampler")
	void OnDisableCheckStats();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartPrimaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopPrimaryAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartSecondaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopSecondaryAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartReloadAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopReloadAction();



	

	// Old unused functions. Removed. /E 16-07-13

	//UFUNCTION()
	//void TriggerEnter(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//UFUNCTION()
	//void TriggerExit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex);

	

	AActor* GetClosestInteractableActor();

	// Changed m_OtherBox into a more generic primitive, more modifiable in BPs. /E, 16-07-13
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UPrimitiveComponent* m_InteractPrimitive = nullptr;

	AActor* m_CurrentUseActor = nullptr;


	// Added UPROPERTY and moved to protected (BlueprintReadWrite doesn't work in private). /E, 16-07-13
	// Removed sampler from equipment - the sampler works differently /E 16-07-25
		//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		//ADEquipment* m_Sampler = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	ADWeapon* m_Weapon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	ADEquipment* m_Equipment = nullptr;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool b_ControlRotationEnabled = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool b_ControlMovementEnabled = true;

	// UGLY: Added speed factor that can be modified by blueprints in runtime. /E 16-08-12
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float m_SpeedFactor = 1.f;
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Movement")
	float GetSpeedFactor() const;
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetSpeedFactor(float newFactor);

	// Update function to update all attributes. Should only be externally through CallUpdateAttributes(), which calls it once in Tick(). 16-07-21 /E
	virtual void UpdateAttributes();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Attributes")
	void OnAttributesUpdated();

	
private:
	
	bool b_NeedAttributeUpdate = false;

	bool b_IsJumping = false;
	float m_SprintAccumulator = 0.f;
	float m_HeightTarget = 0.f;
	
};
