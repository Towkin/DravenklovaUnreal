// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

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

	void MoveForward(float a_Value);

	void MoveRight(float a_Value);

	void Turn(float a_Value);

	void LookUp(float a_Value);

	// ADAttributes* m_Attributes;
	
};
