// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "Ghoul_Ai_CON.h"
#include "Waypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
//#include "DCharacter.h"
#include "AICharacter.h"
#include "BTSelectWaypoint.h"


AGhoul_Ai_CON::AGhoul_Ai_CON()
{
	/* Initilize blackboard and behavior tree*/

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initilize blackboard keys*/
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
}

void AGhoul_Ai_CON::SetPlayerCaught(APawn * Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
	}
}

void AGhoul_Ai_CON::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	/* Get reference to the character */

	AAICharacter* GhoulCharacter = Cast<AAICharacter>(Pawn);

	if (GhoulCharacter)
	{
		if (GhoulCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(GhoulCharacter->BehaviorTree->BlackboardAsset));
		}

		/* Populate patrol point array*/

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*GhoulCharacter->BehaviorTree);
	}
}


