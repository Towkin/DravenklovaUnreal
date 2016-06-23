// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DCharacter.h"


// Sets default values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TODO: Initialize m_Attributes once the class has been written

}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);

	// Calls class methods which in turn call the relevant methods from Pawn.
	// The extra method call allows having a log message for the purpose tracing bugs.
	InputComponent->BindAxis("Turn", this, &ADCharacter::Turn);
	InputComponent->BindAxis("LookUp", this, &ADCharacter::LookUp);

}

void ADCharacter::MoveForward(float a_Value)
{
	if (a_Value != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving forward"));
	}	
}

void ADCharacter::MoveRight(float a_Value)
{
	if (a_Value != 0.0f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving right"));
	}
	
}

void ADCharacter::Turn(float a_Value)
{
	if (a_Value != 0.0f)
	{
		this->AddControllerYawInput(a_Value);
		UE_LOG(LogTemp, Warning, TEXT("Changing direction"));
	}
	
}

void ADCharacter::LookUp(float a_Value)
{
	if (a_Value != 0.0f)
	{
		//Changing the sign of the input value because the Y-axis seems to be reversed.
		this->AddControllerPitchInput(-a_Value);
		UE_LOG(LogTemp, Warning, TEXT("Looking up"));
	}
	
}
