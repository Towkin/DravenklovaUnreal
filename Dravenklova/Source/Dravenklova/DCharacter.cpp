// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DCharacter.h"
#include "DObject.h"
#include "DAttributes.h"
#include "DEquipment.h"
#include "DWeapon.h"

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
	
	// Modification due to cooking error: AttachToComponent -> SetupAttachment as Unreal 4.12 doesn't seem to like the former in constructors... /E 16-07-22
	//m_InteractPrimitive->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	m_InteractPrimitive->SetupAttachment(RootComponent);

	//m_OtherBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OtherBox"));
	//m_OtherBox->bGenerateOverlapEvents = true;
	//m_OtherBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	////This might not be needed if it can be replaced with GetOverlappingActors()
	//m_OtherBox->OnComponentBeginOverlap.AddDynamic(this, &ADCharacter::TriggerEnter);
	//m_OtherBox->OnComponentEndOverlap.AddDynamic(this, &ADCharacter::TriggerExit);

	m_Weapon = nullptr;
	m_Equipment = nullptr;
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

	InputComponent->BindAction("Weapon Primary", IE_Pressed, this, &ADCharacter::StartPrimaryAction);
	InputComponent->BindAction("Weapon Primary", IE_Released, this, &ADCharacter::StopPrimaryAction);

	InputComponent->BindAction("Weapon Secondary", IE_Pressed, this, &ADCharacter::StartSecondaryAction);
	InputComponent->BindAction("Weapon Secondary", IE_Released, this, &ADCharacter::StopSecondaryAction);

	InputComponent->BindAction("Reload", IE_Pressed, this, &ADCharacter::StartReloadAction);
	InputComponent->BindAction("Reload", IE_Released, this, &ADCharacter::StopReloadAction);


	InputComponent->BindAction("DropPrimary", IE_Pressed, this, &ADCharacter::DropWeapon);
	InputComponent->BindAction("DropSecondary", IE_Pressed, this, &ADCharacter::DropEquipment);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ADCharacter::EnableSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ADCharacter::DisableSprint);

	InputComponent->BindAction("Crouch", IE_Pressed, this, &ADCharacter::EnableCrouch);
	InputComponent->BindAction("Crouch", IE_Released, this, &ADCharacter::DisableCrouch);


	// Not done yet
	InputComponent->BindAction("CheckStats", IE_Pressed, this, &ADCharacter::EnableCheckStats);
	InputComponent->BindAction("CheckStats", IE_Released, this, &ADCharacter::DisableCheckStats);

}

ADWeapon* ADCharacter::GetWeapon()
{
	return m_Weapon;
}

void ADCharacter::SetWeapon(ADWeapon* weapon)
{
	m_Weapon = weapon;
	ProvideEquippedWeapon(weapon);
	UE_LOG(LogTemp, Warning, TEXT("Setting as primary: %s"), *weapon->GetName());
}
ADEquipment* ADCharacter::GetEquipment()
{
	return m_Equipment;
}

void ADCharacter::SetEquipment(ADEquipment* equipment)
{
	m_Equipment = equipment;
	ProvideEquippedEquipment(equipment);
	UE_LOG(LogTemp, Warning, TEXT("Setting as Secondary: %s"), *equipment->GetName());
}

void ADCharacter::DropWeapon()
{	
	if (m_Weapon)
	{
		ProvideUnequippedWeapon(m_Weapon);
		m_Weapon->Unequip(this);
		UE_LOG(LogTemp, Warning, TEXT("Droppping Primary:  %s"), *m_Weapon->GetName());
		m_Weapon = nullptr;
	}	
}

void ADCharacter::DropEquipment()
{	
	if (m_Equipment)
	{
		ProvideUnequippedEquipment(m_Equipment);
		m_Equipment->Unequip(this);
		UE_LOG(LogTemp, Warning, TEXT("Droppping Secondary: %s"), *m_Equipment->GetName());
		m_Equipment = nullptr;
	}	
}

void ADCharacter::MoveForward(float a_Value)
{	
	if ((Controller != nullptr) && (a_Value != 0.0f) && b_ControlMovementEnabled)
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
	}
}

void ADCharacter::MoveRight(float a_Value)
{
	if ((Controller != nullptr) && (a_Value != 0.0f) && b_ControlMovementEnabled)
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		// add movement in that direction
		AddMovementInput(Direction, a_Value);
	}	
}

void ADCharacter::Turn(float a_Value)
{
	if (a_Value != 0.0f && b_ControlRotationEnabled)
	{
		this->AddControllerYawInput(a_Value);
	}	
}

void ADCharacter::LookUp(float a_Value)
{
	if (a_Value != 0.0f && b_ControlRotationEnabled)
	{
		this->AddControllerPitchInput(a_Value);
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
void ADCharacter::EndUse()
{
	if (m_CurrentUseActor)
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


void ADCharacter::EnableCheckStats()
{
	// Um... Animate check stats stuff
	//UE_LOG(LogTemp, Warning, TEXT("Checking Stats..."));
	OnEnableCheckStats();
}

void ADCharacter::DisableCheckStats()
{
	//UE_LOG(LogTemp, Warning, TEXT("Not Checking Stats..."));
	OnDisableCheckStats();
}

void ADCharacter::StartPrimaryAction()
{
	OnStartPrimaryAction();
	if (m_Weapon)
	{
		m_Weapon->PrimaryActionBegin();
	}
}

void ADCharacter::StopPrimaryAction()
{
	OnStopPrimaryAction();
	if (m_Weapon)
	{
		m_Weapon->PrimaryActionEnd();
	}
}

void ADCharacter::StartSecondaryAction()
{
	OnStartSecondaryAction();
	if (m_Weapon)
	{
		m_Weapon->SecondaryActionBegin();
	}
}

void ADCharacter::StopSecondaryAction()
{
	OnStopSecondaryAction();
	if (m_Weapon)
	{
		m_Weapon->SecondaryActionEnd();
	}
}

void ADCharacter::StartReloadAction()
{
	OnStartReloadAction();
	if (m_Weapon)
	{
		m_Weapon->ReloadActionBegin();
	}
}

void ADCharacter::StopReloadAction()
{
	OnStopReloadAction();
	if (m_Weapon)
	{
		m_Weapon->ReloadActionEnd();
	}
}


AActor* ADCharacter::GetClosestInteractableActor()
{
	//UE_LOG(LogTemp, Warning, TEXT("Looking for object to interact with."))

	//TArray<AActor*> listOfActors;
	//m_InteractPrimitive->GetOverlappingActors(listOfActors);
	TArray<UPrimitiveComponent*> listOfPrimitives;
	m_InteractPrimitive->GetOverlappingComponents(listOfPrimitives);

	//Check that the array is not empty
	//if (listOfActors.Num() == 0)
	if (listOfPrimitives.Num() == 0)
	{ 
		UE_LOG(LogTemp, Warning, TEXT("No overlapping actors."))
		return nullptr;
	}
	
	//AActor* closestActor = nullptr;
	UPrimitiveComponent* closestPrimitive = nullptr;
	IInteractInterface* myInterface = nullptr;

	//Iterate through the array to find the member nearest to the character
	//for (auto& actor : listOfActors)
	for (auto& primitive : listOfPrimitives)
	{
		//Compare the distances between the character and the actors

		//if (closestActor == nullptr || GetDistanceTo(actor) < GetDistanceTo(closestActor))
		if (closestPrimitive == nullptr || FVector::Dist(primitive->GetComponentLocation(), GetActorLocation()) < FVector::Dist(closestPrimitive->GetComponentLocation(), GetActorLocation()))
		{
			AActor* actor = primitive->GetOwner();

			// If the actor is already equipped, skip /E, 16-07-13
			if (actor == this || actor == m_Weapon || actor == m_Equipment) {
				continue;
			}

			//Only replace if interactable
			IInteractInterface* actorAsInterface = Cast<IInteractInterface>(actor);
			
			if (actorAsInterface)
			{
				myInterface = actorAsInterface;
				closestPrimitive = primitive;
			}			
		}
	}
	
	if (!myInterface)
	{
		UE_LOG(LogTemp, Warning, TEXT("No overlapping interactable actors."))
		return nullptr;
	}	
	
	UE_LOG(LogTemp, Warning, TEXT("Found closest actor"))
	return Cast<AActor>(myInterface);
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
	GetCharacterMovement()->JumpZVelocity = m_Attributes->getJumpForce();
	m_HeightTarget = m_Attributes->getCurrentCharacterHeight() / 2;
	

	OnAttributesUpdated();

	b_NeedAttributeUpdate = false;
}
