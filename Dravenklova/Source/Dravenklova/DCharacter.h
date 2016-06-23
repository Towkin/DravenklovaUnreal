// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UDAttributes;

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

	

protected:
	UDAttributes* m_Attributes = nullptr;

	void MoveForward(float a_Value);

	void MoveRight(float a_Value);

	void Turn(float a_Value);

	void LookUp(float a_Value);

	void OnStartJump();

	void OnStopJump();

	void Interact();

	//Should contain reference to object as argument
	void Use();

	void Equip();

private:
	bool b_IsJumping = false;



	
};
