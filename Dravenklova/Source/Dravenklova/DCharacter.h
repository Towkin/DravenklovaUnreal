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
	ADCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = "true"))
	UDAttributes* m_Attributes;

	virtual void OnConstruction(const FTransform& Transform) override;

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
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	ADWeapon* GetWeapon();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetWeapon(ADWeapon* weapon);
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	ADEquipment* GetEquipment();
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

protected:

	void MoveForward(float a_Value);
	void MoveRight(float a_Value);

	void Turn(float a_Value);
	void LookUp(float a_Value);

	void StartJump();
	void StopJump();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnStartJump();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnStopJump();

	
	void EnableSprint();
	void DisableSprint();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnSprintEnabled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnSprintDisabled();

	void EnableCrouch();
	void DisableCrouch();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnCrouchEnabled();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Movement")
	void OnCrouchDisabled();

	void EnableCheckStats();
	void DisableCheckStats();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sampler")
	void OnEnableCheckStats();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Sampler")
	void OnDisableCheckStats();
	

	// Primary Equipment (Weapon) actions /E 16-07-25
	void StartPrimaryAction();
	void StopPrimaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartPrimaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopPrimaryAction();

	void StartSecondaryAction();
	void StopSecondaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartSecondaryAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopSecondaryAction();

	void StartReloadAction();
	void StopReloadAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStartReloadAction();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Weapon")
	void OnStopReloadAction();




	void Use();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void EndUse();

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
