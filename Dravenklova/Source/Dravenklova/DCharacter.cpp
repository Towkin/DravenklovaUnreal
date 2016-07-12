// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DCharacter.h"
#include "DObject.h"
#include "DAttributes.h"
#include "DEquipment.h"


// Sets default a_Values
ADCharacter::ADCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_Attributes = CreateDefaultSubobject<UDAttributes>(TEXT("AttributesComponent"));
	if (!m_Attributes)
	{
		UE_LOG(LogTemp, Warning, TEXT("has attributes not"));
	}

	m_OtherBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OtherBox"));
	m_OtherBox->bGenerateOverlapEvents = true;
	m_OtherBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//This might not be needed if it can be replaced with GetOverlappingActors()
	m_OtherBox->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::TriggerEnter);
	m_OtherBox->OnComponentEndOverlap.AddDynamic(this, &ADCharacter::TriggerExit);

	UE_LOG(LogTemp, Warning, TEXT("Character constructor"));
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getBaseSpeed();
	m_Primary = nullptr;
	m_Secondary = nullptr;
}
void ADCharacter::OnConstruction(const FTransform& Transform)
{
	GetCapsuleComponent()->SetCapsuleHalfHeight(m_Attributes->getCharacterHeight() / 2);
	GetCapsuleComponent()->SetCapsuleRadius(m_Attributes->getCharacterRadius());
	m_HeightTarget = m_Attributes->getCharacterHeight() / 2;

	m_Attributes->UpdateAttributes();
}
// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
	DisableSprint();
	
}

// Called every frame
void ADCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	float CapsuleHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	if (CapsuleHalfHeight != m_HeightTarget) {
		float CrouchSpeed = 350.f * DeltaTime;
		float Diff = m_HeightTarget - CapsuleHalfHeight;
		GetCapsuleComponent()->SetCapsuleHalfHeight(CapsuleHalfHeight + FMath::Sign(Diff) * FMath::Min(CrouchSpeed, FMath::Abs(Diff)));
	}

	if (m_Attributes->b_IsSprinting) {
		float Product = FVector::DotProduct(GetActorForwardVector(), GetCharacterMovement()->GetLastInputVector());
		if (Product < 0.5f) {
			UE_LOG(LogTemp, Warning, TEXT("Product: %d"), Product);
			DisableSprint();
		}
		m_SprintAccumulator -= DeltaTime;
		if (m_SprintAccumulator <= 0.f) {
			DisableSprint();
		}
		// TODO: Check sprint time
	}
	else 
	{
		m_SprintAccumulator = FMath::Min(m_SprintAccumulator + (DeltaTime * (m_Attributes->getSprintingTime() / m_Attributes->getSprintingRechargeTime())), m_Attributes->getSprintingTime());
	}


}

	//Call OnStopJump after certain time
	//Reset jumptimer?



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

	InputComponent->BindAction("Use", IE_Pressed, this, &ADCharacter::Use);
	InputComponent->BindAction("Use", IE_Released, this, &ADCharacter::EndUse);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ADCharacter::EnableSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ADCharacter::DisableSprint);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &ADCharacter::EnableCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ADCharacter::DisableCrouch);


	// Not done yet
	InputComponent->BindAction("CheckStats", IE_Pressed, this, &ADCharacter::EnableCheckStats);
	InputComponent->BindAction("CheckStats", IE_Released, this, &ADCharacter::DisableCheckStats);

}

ADEquipment* ADCharacter::GetPrimary()
{
	// TODO: insert return statement here
	return m_Primary;
}

void ADCharacter::SetPrimary(ADEquipment * equipment)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting primary"));
}
ADEquipment* ADCharacter::GetSecondary()
{
	// TODO: insert return statement here
	return m_Secondary;
}

void ADCharacter::SetSecondary(ADEquipment * equipment)
{
	UE_LOG(LogTemp, Warning, TEXT("Setting Secondary"));
}

void ADCharacter::MoveForward(float a_Value)
{	
	if ((Controller != nullptr) && (a_Value != 0.0f))
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
		AddMovementInput(Direction, a_Value * m_Attributes->getBaseSpeed());

		//UE_LOG(LogTemp, Warning, TEXT("Moving forward"));
	}
}

void ADCharacter::MoveRight(float a_Value)
{
	if ((Controller != nullptr) && (a_Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, a_Value* m_Attributes->getBaseSpeed());

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
}

void ADCharacter::OnStopJump()
{
	if (b_IsJumping)
	{
		bPressedJump = false;

		b_IsJumping = false;

		//Reset jumptimer?		
	}	
	else
	{
	}
}


void ADCharacter::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Use ..."));

	//Returns the closest interactable actor
	//If no overlapping actors, returns null

	AActor* object = GetClosestInteractableActor();

	if (object)
	{
		IInteractInterface* myInterface = Cast<IInteractInterface>(object);
		if (myInterface)
		{
			UE_LOG(LogTemp, Warning, TEXT("Found something to interact with."));
			
			EndUse();

			myInterface->Interact(this);
			m_CurrentUseActor = object;
			ProvideInteractBegin(m_CurrentUseActor);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("This object is not interactable."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No interactable objects within range."));
	}
}

void ADCharacter::EnableSprint()
{
	if (m_Attributes->b_IsCrouching)
	{
		return;
	}
	m_Attributes->b_IsSprinting = true;
	
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getBaseSpeed() * m_Attributes->getSprintingSpeedFactor();
}

void ADCharacter::DisableSprint()
{
	m_Attributes->b_IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getBaseSpeed();
}

void ADCharacter::EnableCrouch()
{
	m_Attributes->b_IsCrouching = true;
	DisableSprint();
	m_HeightTarget = m_Attributes->getCharacterCrouchHeight() / 2;
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getBaseSpeed() * m_Attributes->getCrouchSpeedFactor();
}

void ADCharacter::DisableCrouch()
{
	m_Attributes->b_IsCrouching = false;
	m_HeightTarget = m_Attributes->getCharacterHeight() / 2;
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getBaseSpeed();
}

void ADCharacter::EndUse()
{
	if(m_CurrentUseActor)
	{
		IInteractInterface* lastInteractObject = Cast<IInteractInterface>(m_CurrentUseActor);
		if (lastInteractObject)
		{
			lastInteractObject->EndInteract(this);
		}

		ProvideInteractEnd(m_CurrentUseActor);
		m_CurrentUseActor = nullptr;
	}
}

void ADCharacter::EnableCheckStats()
{
	// Um... Animate check stats stuff
	UE_LOG(LogTemp, Warning, TEXT("Checking Stats..."));

}

void ADCharacter::DisableCheckStats()
{
	UE_LOG(LogTemp, Warning, TEXT("Not Checking Stats..."));
}

void ADCharacter::Equip()
{
	UE_LOG(LogTemp, Warning, TEXT("Equip ..."));
}

void ADCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attacking..."));
}

void ADCharacter::TriggerEnter(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Added %s with index %d"), *OtherActor->GetName(), OtherBodyIndex);

	//Light->SetLightColor(FColor::Green);
	//add otherActor to list
}

void ADCharacter::TriggerExit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	//UE_LOG(LogTemp, Warning, TEXT("Removed %s with index %d"), *OtherActor->GetName(), OtherBodyIndex);

	//Light->SetLightColor(FColor::Red);
	//remove otheractor from list
}

AActor* ADCharacter::GetClosestInteractableActor()
{
	//UE_LOG(LogTemp, Warning, TEXT("Looking for object to interact with."))
	TArray<AActor*> listOfActors;
	m_OtherBox->GetOverlappingActors(listOfActors);
	
	//Check that the array is not empty
	if (listOfActors.Num() == 0)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No overlapping actors."))
		return nullptr;
	}
	
	AActor* closestActor = nullptr;
	
	//Iterate through the array to find the member nearest to the character
	for (auto& actor : listOfActors)
	{
		//Compare the distances between the character and the actors
		if (closestActor == nullptr || GetDistanceTo(actor) < GetDistanceTo(closestActor))
		{
			//Only replace if interactable
			IInteractInterface* myInterface = Cast<IInteractInterface>(actor);
			if (myInterface)
			{
				closestActor = actor;
			}			
		}
	}

	//TODO: remove superfluous casts
	IInteractInterface* myInterface = closestActor ? Cast<IInteractInterface>(closestActor) : nullptr;
	
	if (!myInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("No overlapping interactable actors."))
		return nullptr;
	}	
	
	UE_LOG(LogTemp, Warning, TEXT("Found closest actor"))
	return closestActor;
}
