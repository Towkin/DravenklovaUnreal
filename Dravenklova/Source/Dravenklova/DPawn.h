// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DPawn.generated.h"

UCLASS()
class DRAVENKLOVA_API ADPawn : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ADPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	virtual void MoveForward(float a_Value);
	
protected:


	UCameraComponent* MyCamera;
	USpringArmComponent* MyCameraSpringArm;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DPawn")
	float m_Speed;
	
};
