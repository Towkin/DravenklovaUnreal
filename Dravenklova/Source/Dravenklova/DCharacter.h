// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UDAttributes;
class IInteractInterface;

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UDAttributes* m_Attributes = nullptr;
	virtual void OnConstruction(const FTransform& Transform) override;

protected:

	void MoveForward(float a_Value);

	void MoveRight(float a_Value);

	void Turn(float a_Value);

	void LookUp(float a_Value);

	void OnStartJump();

	void OnStopJump();

	void EnableSprint();

	void DisableSprint();
	
	void EnableCrouch();
	
	void DisableCrouch();

	void EnableCheckStats();

	void DisableCheckStats();
	
	void Attack();

	void Use();

	void EndUse();

	void Equip();
	
	UFUNCTION()
	void TriggerEnter(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TriggerExit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherCOmp, int32 OtherBodyIndex);

	AActor* GetClosestInteractableActor();

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = TriggerBox)
		UBoxComponent* m_OtherBox = nullptr;

	IInteractInterface* m_CurrentUseObject = nullptr;

private:
	bool b_IsJumping = false;	
	float m_SprintAccumulator = 0.f;
	float m_HeightTarget = 0.f;
};
