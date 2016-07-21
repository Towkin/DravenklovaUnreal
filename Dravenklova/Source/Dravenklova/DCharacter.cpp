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

	// Changed m_OtherBox behaviours into more general m_InteractPrimitive behaviours. /E 16-07-13

	m_InteractPrimitive = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	m_InteractPrimitive->bGenerateOverlapEvents = true;
	m_InteractPrimitive->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//m_OtherBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OtherBox"));
	//m_OtherBox->bGenerateOverlapEvents = true;
	//m_OtherBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	////This might not be needed if it can be replaced with GetOverlappingActors()
	//m_OtherBox->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::TriggerEnter);
	//m_OtherBox->OnComponentEndOverlap.AddDynamic(this, &ADCharacter::TriggerExit);

	m_Primary = nullptr;
	m_Secondary = nullptr;
	m_Sampler = nullptr;


	UpdateAttributes();
}
void ADCharacter::OnConstruction(const FTransform& Transform)
{
	m_Attributes->UpdateAttributes();
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(m_Attributes->getCharacterHeight() / 2);
	GetCapsuleComponent()->SetCapsuleRadius(m_Attributes->getCharacterRadius());
	m_HeightTarget = m_Attributes->getCharacterHeight() / 2;
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

	// UpdateAttributes call - 16-07-21 /E
	if (b_NeedAttributeUpdate)
	{
		UpdateAttributes();
	}

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
	}
	else 
	{
		m_SprintAccumulator = FMath::Min(m_SprintAccumulator + (DeltaTime * (m_Attributes->getSprintingTime() / m_Attributes->getSprintingRechargeTime())), m_Attributes->getSprintingTime());
	}
}

	//Call OnStopJump after certain time
	//Reset jumptimer?s

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
	InputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ADCharacter::StopJump);

	InputComponent->BindAction("Use", IE_Pressed, this, &ADCharacter::Use);
	InputComponent->BindAction("Use", IE_Released, this, &ADCharacter::EndUse);

	InputComponent->BindAction("DropPrimary", IE_Pressed, this, &ADCharacter::DropPrimary);
	InputComponent->BindAction("DropSecondary", IE_Pressed, this, &ADCharacter::DropSecondary);

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
	return m_Primary;
}

void ADCharacter::SetPrimary(ADEquipment * equipment)
{
	m_Primary = equipment;
	ProvideEquippedPrimary(equipment);
	UE_LOG(LogTemp, Warning, TEXT("Setting as primary: %s"), *equipment->GetName());
}
ADEquipment* ADCharacter::GetSecondary()
{
	return m_Secondary;
}

void ADCharacter::SetSecondary(ADEquipment * equipment)
{
	m_Secondary = equipment;
	ProvideEquippedSecondary(equipment);
	UE_LOG(LogTemp, Warning, TEXT("Setting as Secondary: %s"), *equipment->GetName());
}

void ADCharacter::DropPrimary()
{	
	if (m_Primary)
	{
		ProvideUnequippedPrimary(m_Primary);
		m_Primary->Unequip(this);
		UE_LOG(LogTemp, Warning, TEXT("Droppping Primary:  %s"), *m_Primary->GetName());
		m_Primary = nullptr;
	}	
}

void ADCharacter::DropSecondary()
{	
	if (m_Secondary)
	{
		ProvideUnequippedSecondary(m_Secondary);
		m_Secondary->Unequip(this);
		UE_LOG(LogTemp, Warning, TEXT("Droppping Secondary: %s"), *m_Secondary->GetName());
		m_Secondary = nullptr;
	}	
}

void ADCharacter::SetSampler(ADEquipment* a_Sampler)
{
	if (!m_Sampler)
	{
		UE_LOG(LogTemp, Warning, TEXT("Picking up sampler"));
		m_Sampler = a_Sampler;
	}
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
		AddMovementInput(Direction, a_Value);

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


void ADCharacter::StartJump()
{
	bPressedJump = true;
	b_IsJumping = true;

	OnStartJump();
}

void ADCharacter::StopJump()
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

	OnStopJump();
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
	CallUpdateAttributes();

	OnSprintEnabled();
}

void ADCharacter::DisableSprint()
{
	m_Attributes->b_IsSprinting = false;
	CallUpdateAttributes();

	OnSprintDisabled();
}

void ADCharacter::EnableCrouch()
{
	m_Attributes->b_IsCrouching = true;
	DisableSprint();
	CallUpdateAttributes();

	OnCrouchEnabled();
}

void ADCharacter::DisableCrouch()
{
	m_Attributes->b_IsCrouching = false;
	CallUpdateAttributes();

	OnCrouchDisabled();
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

// Old unused functions. Removed. /E 16-07-13

//void ADCharacter::TriggerEnter(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("Added %s with index %d"), *OtherActor->GetName(), OtherBodyIndex);
//
//	//Light->SetLightColor(FColor::Green);
//	//add otherActor to list
//}
//
//void ADCharacter::TriggerExit(UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//
//	//UE_LOG(LogTemp, Warning, TEXT("Removed %s with index %d"), *OtherActor->GetName(), OtherBodyIndex);
//
//	//Light->SetLightColor(FColor::Red);
//	//remove otheractor from list
//}

AActor* ADCharacter::GetClosestInteractableActor()
{
	//UE_LOG(LogTemp, Warning, TEXT("Looking for object to interact with."))
	TArray<AActor*> listOfActors;

	m_InteractPrimitive->GetOverlappingActors(listOfActors);

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
			// If the actor is already equipped, skip /E, 16-07-13
			if (actor == m_Primary || actor == m_Secondary || actor == m_Sampler) {
				continue;
			}

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

void ADCharacter::CallUpdateAttributes()
{
	b_NeedAttributeUpdate = true;
}

void ADCharacter::UpdateAttributes()
{
	m_Attributes->UpdateAttributes();

	// All character values which rely on m_Attributes are updated below.
	GetCharacterMovement()->MaxWalkSpeed = m_Attributes->getCurrentMaxSpeed();
	GetCharacterMovement()->JumpZVelocity = m_Attributes->getJumpForce() / GetCharacterMovement()->Mass;
	m_HeightTarget = m_Attributes->getCurrentCharacterHeight() / 2;
	

	OnAttributesUpdated();

	b_NeedAttributeUpdate = false;
}
