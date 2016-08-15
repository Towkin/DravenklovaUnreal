// Fill out your copyright notice in the Description page of Project Settings.
//https://www.unrealengine.com/blog/damage-in-ue4
//https://www.youtube.com/watch?v=8RuMckVAA4c
//https://www.youtube.com/watch?v=0S725kCMtlo
//https://www.youtube.com/watch?v=FGfIbvFL31I
#include "Dravenklova.h"
#include "AICharacter.h"

#include "Ghoul_Ai_CON.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AAICharacter::AAICharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	/* Initialize senses */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnsensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
	PawnSensingComp->SightRadius = 500.f;
	//m_LastSeenLocation = FVector(0.f, 0.f, 0.f);
}
void AAICharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnPawnCaught);
		
	}
}
void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void AAICharacter::OnPawnCaught(APawn* Pawn)
{
	
	AGhoul_Ai_CON* GhoulCont = Cast<AGhoul_Ai_CON>(GetController());

	if (GhoulCont)
	{
		GhoulCont->SetPawnCaught(Pawn);
		
		//GhoulCont->CanSeePawn(Pawn);
	//		SetLastSeenLocation(Pawn);
	}

	//SetLastSeenLocation(Pawn);
}
/*void AAICharacter::SetLastSeenLocation(APawn* Pawn)
{
	AGhoul_Ai_CON* GhoulCont = Cast<AGhoul_Ai_CON>(GetController());
	
	if (GhoulCont)
	{
		//m_LastSeenLocation = Pawn->GetActorLocation();
		GhoulCont->CanSeePawn(Pawn);
		
	}
}*/