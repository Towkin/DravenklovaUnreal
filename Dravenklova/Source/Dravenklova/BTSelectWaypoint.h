// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectWaypoint.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API UBTSelectWaypoint : public UBTTaskNode
{
	GENERATED_BODY()
	
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
public:
	UPROPERTY(EditAnywhere, Category = "AI")
		FVector LastSeenLocation;
	
	
	
};
