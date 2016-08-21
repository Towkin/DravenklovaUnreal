// Fill out your copyright notice in the Description page of Project Settings.
//https://www.unrealengine.com/blog/damage-in-ue4
//https://www.youtube.com/watch?v=8RuMckVAA4c
//https://www.youtube.com/watch?v=0S725kCMtlo
//https://www.youtube.com/watch?v=FGfIbvFL31I
#include "Dravenklova.h"
#include "AICharacter.h"
#include "DAttributes.h"

#include "Ghoul_Ai_CON.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

ADNonPlayableCharacter::ADNonPlayableCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	/* Initialize senses */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnsensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(75.f);
	PawnSensingComp->SightRadius = 500.f;

	

	//m_Box = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackRangeCollisionBox"));
	//m_Box->AttachTo(RootComponent);
	//m_LastSeenLocation = FVector(0.f, 0.f, 0.f);
}
void ADNonPlayableCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ADNonPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ADNonPlayableCharacter::OnPawnCaught);
	}
}
void ADNonPlayableCharacter::Tick(float DeltaSeconds)
{	
	Super::Tick(DeltaSeconds);
	
	ADCharacter* DChar = Cast<ADCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (DChar)
	{
		HasLineOfSight = PawnSensingComp->HasLineOfSightTo(DChar);

		if (HasLineOfSight)
		{
			//UE_LOG(LogTemp, Warning, TEXT("I can see the player"));
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("I can't see the player"));
		}
		//if (!PawnSensingComp->HasLineOfSightTo(DChar))
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("I can see player"));
		//	IsLineOfSight = false;
		//}
	}
}
	
void ADNonPlayableCharacter::OnPawnCaught(APawn* Pawn)
{
	
}

void ADNonPlayableCharacter::UpdateAttributes()
{
	Super::UpdateAttributes();

	PawnSensingComp->SightRadius = m_Attributes->getViewDistance();
	

}