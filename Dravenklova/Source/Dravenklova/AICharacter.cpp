// Fill out your copyright notice in the Description page of Project Settings.
//https://www.unrealengine.com/blog/damage-in-ue4
#include "Dravenklova.h"
#include "AICharacter.h"

#include "Ghoul_Ai_CON.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

AAICharacter::AAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	/* Initialize senses */
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnsensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
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
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAICharacter::OnPlayerCaught);
	}
}
void AAICharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
void AAICharacter::OnPlayerCaught(APawn* Pawn)
{
	AGhoul_Ai_CON * GhoulCont = Cast<AGhoul_Ai_CON>(GetController());

	if (GhoulCont)
	{
		GhoulCont->SetPlayerCaught(Pawn);

	}
}