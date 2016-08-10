// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Ghoul_Ai_CON.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API AGhoul_Ai_CON : public AAIController
{
	GENERATED_BODY()

	/* Behavior tree component*/
	UBehaviorTreeComponent* BehaviorComp;

	/* Our blackboard component*/
	UBlackboardComponent* BlackboardComp;
	/* Blackboard keys*/

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LocationToGoKey;

	TArray<AActor*> PatrolPoints;

	virtual void Possess(APawn* Pawn) override;
	
public:

	AGhoul_Ai_CON();

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PlayerKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;

	void SetPlayerCaught(APawn* Pawn);

	int32 CurrentPatrolPoint;

	/* Inline getter functions */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const
	{
		return BlackboardComp;
	}
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const
	{
		return PatrolPoints;
	}

	
	
	
};
