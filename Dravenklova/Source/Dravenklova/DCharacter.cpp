// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DCharacter.h"
#include "DAttributes.h"


// Sets default a_Values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TODO: Initialize m_Attributes once the class has been written
	m_Attributes = NewObject<UDAttributes>();

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

	//Call OnStopJump after certain time
	//Reset jumptimer?

}

// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);

	// Calls class methods which in turn call the relevant methods from Pawn.
	// The extra method call allows having a log message for the purpose of tracing bugs.
	InputComponent->BindAxis("Turn", this, &ADCharacter::Turn);
	InputComponent->BindAxis("LookUp", this, &ADCharacter::LookUp);

	// Jump
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::OnStartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ADCharacter::OnStopJump);

	InputComponent->BindAction("Interact", IE_Pressed, this, &ADCharacter::Interact);
}

void ADCharacter::MoveForward(float a_Value)
{	
	if ((Controller != NULL) && (a_Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();

		//Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}

		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, a_Value);

		//UE_LOG(LogTemp, Warning, TEXT("Moving forward"));
	}
}

void ADCharacter::MoveRight(float a_Value)
{
	if ((Controller != NULL) && (a_Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, a_Value);

		//UE_LOG(LogTemp, Warning, TEXT("Moving right"));
	}	
}

void ADCharacter::Turn(float a_Value)
{
	if (a_Value != 0.0f)
	{
		this->AddControllerYawInput(a_Value);

		//UE_LOG(LogTemp, Warning, TEXT("Changing direction"));
	}	
}

void ADCharacter::LookUp(float a_Value)
{
	if (a_Value != 0.0f)
	{
		//Changing the sign of the input a_Value because the Y-axis seems to be reversed.
		this->AddControllerPitchInput(-a_Value);

		//UE_LOG(LogTemp, Warning, TEXT("Looking up"));
	}	
}


void ADCharacter::OnStartJump()
{
	bPressedJump = true;
	b_IsJumping = true;

	UE_LOG(LogTemp, Warning, TEXT("Start jumping!"));
}

void ADCharacter::OnStopJump()
{
	if (b_IsJumping)
	{
		bPressedJump = false;

		b_IsJumping = false;

		//Reset jumptimer?

		UE_LOG(LogTemp, Warning, TEXT("Stop jumping!"));		
	}	
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("We are not jumping, stop shouting"));
	}
}


void ADCharacter::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("Interact with ..."));

	//if(object == weapon) Equip(object);
	//if(object == other) Use(object);
}

void ADCharacter::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Use ..."));
}

void ADCharacter::Equip()
{
	UE_LOG(LogTemp, Warning, TEXT("Equip ..."));
}