// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "BTSelectWaypoint.h"
#include "Waypoint.h"
#include "Ghoul_Ai_CON.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTSelectWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AGhoul_Ai_CON* GhoulCon = Cast<AGhoul_Ai_CON>(OwnerComp.GetAIOwner());

	if (GhoulCon && GhoulCon->GetPatrolPoints().Num() > 0)
	{
		/* Get BB Component*/
		UBlackboardComponent* BlackboardComp = GhoulCon->GetBlackboardComp();

		AWaypoint* CurrentPoint = Cast<AWaypoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		/* Creating TArray to store the patrolPoints */
		TArray<AActor*> AvailablePatrolPoints = GhoulCon->GetPatrolPoints();

		AWaypoint* NextPatrolPoint = nullptr;
		/* If CurrentPatrolPoint is over the last index of the TArray */
		if (GhoulCon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AWaypoint>(AvailablePatrolPoints[++GhoulCon->CurrentPatrolPoint]);
		}
		else /* If there is no more points to go to */
		{
			NextPatrolPoint = Cast<AWaypoint>(AvailablePatrolPoints[0]);
			GhoulCon->CurrentPatrolPoint = 0;
		}

		BlackboardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;

	}

	return EBTNodeResult::Failed;

}