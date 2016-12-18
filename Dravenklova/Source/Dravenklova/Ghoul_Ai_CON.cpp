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
	PrimaryActorTick.bCanEverTick = true;

	/* Initilize blackboard and behavior tree*/

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	// Initilize blackboard keys*/
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
	LastSeenLocation = "LastSeenLocation";
}

void AGhoul_Ai_CON::BeginPlay()
{
	Super::BeginPlay();
	
	

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(UpdateAITimer, this, &AGhoul_Ai_CON::UpdateAI, 0.1f, true);

		if (GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			m_Player = Cast<ADCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		}
	}
}

void AGhoul_Ai_CON::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AGhoul_Ai_CON::UpdateAI()
{
	if (BlackboardComp && m_ControlledCharacter && m_Player)
	{
		FVector PlayerAIDirection = m_Player->GetActorLocation() - m_ControlledCharacter->GetActorLocation();
		
		//IsOverZero = FVector::DotProduct(m_AngleFromAI, m_AngleFromPlayer);
		 
	     float PlayerDirectionProduct = FVector::DotProduct(m_ControlledCharacter->GetActorForwardVector(), PlayerAIDirection);

		
		 if (PlayerDirectionProduct > 0)
		 {
			 UE_LOG(LogTemp, Warning, TEXT("Should see player"));
			

				 // Set PlayerKey to m_Player when m_ControlledCharacter has line of sight, else set to nullptr.
			 BlackboardComp->SetValueAsObject(PlayerKey,
				 (m_ControlledCharacter->HasLineOfSight ? m_Player : nullptr)
				 );


			 // Update the LastSeenLocation key when m_ControllerCharacter has line of sight.
			 if (m_Player && m_ControlledCharacter->HasLineOfSight)
			 {
				 m_LastSeenLocation = m_Player->GetActorLocation();
				 BlackboardComp->SetValueAsVector(LastSeenLocation, m_LastSeenLocation);

				 m_InAttackRangeVector = (m_ControlledCharacter->GetActorLocation() - m_Player->GetActorLocation());
				 m_InAttackRangeFloat = m_InAttackRangeVector.Size();
				 //if (m_ControlledCharacter->GetDistanceTo(m_Player) <= m_InAttackRangeFloat)
				 if(m_InAttackRangeFloat <= m_InAttackRange)
				 {
					 UE_LOG(LogTemp, Warning, TEXT("Attacking"));
					 //UE_LOG(LogTemp, Warning, TEXT("Vector Distance %s"), m_InAttackRangeVector.ToString());

					 /* TODO: Play Ghoul Attack Animation, StopPrimary attack.*/
					/*		  Take damage 	*/
					 m_ControlledCharacter->StartPrimaryAction();

					 
					
				 }
			 }

		 }
	}
}

//void AGhoul_Ai_CON::SetPawnCaught(APawn * Pawn)
//{
//		
//	AAICharacter* GhoulCharacter = Cast<AAICharacter>(Pawn);
//	m_LastSeenLocation = Pawn->GetActorLocation();
//	
//	
//	if (BlackboardComp)
//	{
//		BlackboardComp->SetValueAsObject(PlayerKey, Pawn);
//		BlackboardComp->SetValueAsVector(LastSeenLocation, m_LastSeenLocation);
//		
//		if(GhoulCharacter && GhoulCharacter->IsLineOfSight != true)
//		{
//			BlackboardComp->SetValueAsObject(PlayerKey, nullptr);
//			UE_LOG(LogTemp, Warning, TEXT("Set PlayerKey to NULL"));
//		}
//	}
//}

void AGhoul_Ai_CON::Possess(APawn * Pawn)
{
	Super::Possess(Pawn);

	/* Get reference to the character */
	m_ControlledCharacter = Cast<ADNonPlayableCharacter>(Pawn);

	if (m_ControlledCharacter)
	{
		if (m_ControlledCharacter->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(m_ControlledCharacter->BehaviorTree->BlackboardAsset));
		}

		/* Populate patrol point array*/

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaypoint::StaticClass(), PatrolPoints);

		BehaviorComp->StartTree(*(m_ControlledCharacter->BehaviorTree));
	}
}
