// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "ResetTarget.h"
#include "Ghoul_Ai_CON.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UResetTarget::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

	AGhoul_Ai_CON* GhoulCont = Cast<AGhoul_Ai_CON>(OwnerComp.GetAIOwner());

	if (GhoulCont)
	{
		UBlackboardComponent* BlackboardComp = GhoulCont->GetBlackboardComp();

		if (GhoulCont->PlayerKey == "Target")
		{
			UE_LOG(LogTemp, Warning, TEXT("Reseting Target"));
			BlackboardComp->SetValueAsObject(GhoulCont->PlayerKey, nullptr);
		}
	}
	
	return EBTNodeResult::Type();
}

