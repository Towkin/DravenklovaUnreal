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


AGhoul_Ai_CON::AGhoul_Ai_CON(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	/* Initilize blackboard and behavior tree*/

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initilize blackboard keys*/
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
	LastSeenLocation = "LastSeenLocation";
}

void AGhoul_Ai_CON::SetPawnCaught(APawn * Pawn)
{
	AAICharacter* GhoulCharacter = Cast<AAICharacter>(Pawn);
	//GhoulCharacter->m_LastSeenLocation = Pawn->GetActorLocation();
	//AAIController* GhoulCont = Cast<AAIController>(Pawn);

	m_LastSeenLocation = Pawn->GetActorLocation();
	
	
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
		//BlackboardComp->SetValueAsVector(LastSeenLocation, GhoulCharacter->m_LastSeenLocation);
		BlackboardComp->SetValueAsVector(LastSeenLocation, m_LastSeenLocation);
		//if (GhoulCharacter)
		//{
			//UE_LOG(LogTemp, Warning, TEXT("IsGhoulCharacter"));
			
			//if (GhoulCont)
			//{
				//UE_LOG(LogTemp, Warning, TEXT("IsGhoulCont"));
				
			//}
		//}

		
		
			
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
/*void AGhoul_Ai_CON::CanSeePawn(APawn* Pawn)
{
	if (BlackboardComp)
	{
		AAICharacter* GhoulCharacter = Cast<AAICharacter>(Pawn);

		if (GhoulCharacter)
		{
			GhoulCharacter->m_LastSeenLocation = Pawn->GetActorLocation();
			//Blackboard->SetValueAsVector(LastSeenLocation, GhoulCharacter->m_LastSeenLocation);
			BlackboardComp->SetValueAsVector(LastSeenLocation, GhoulCharacter->m_LastSeenLocation);
		}
	}
}

*/
