// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"

#include "DCharacter.generated.h"

class UDAttributes;
class IInteractInterface;
class ADEquipment;
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
	void ProvideEquippedPrimary(ADEquipment* equipment);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideUnequippedPrimary(ADEquipment* equipment);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideEquippedSecondary(ADEquipment* equipment);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Equipment")
	void ProvideUnequippedSecondary(ADEquipment* equipment);

	// Added UFUNCTION calls /E, 16-07-13
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	ADEquipment* GetPrimary();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetPrimary(ADEquipment* equipment);
	
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	ADEquipment* GetSecondary();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetSecondary(ADEquipment* equipment);

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void DropPrimary();
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void DropSecondary();

	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void SetSampler(ADEquipment* a_Sampler);

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
	
	void Attack();
	void Use();
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void EndUse();
	void Equip();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	ADEquipment* m_Sampler = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	ADEquipment* m_Primary = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
	ADEquipment* m_Secondary = nullptr;

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
