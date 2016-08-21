// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Ghoul_Ai_CON.generated.h"

/**
 * 
 */


class ADCharacter;
class ADNonPlayableCharacter;
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
protected:

	//TArray<APawn*> m_Targets;

	ADCharacter* m_Player = nullptr;

	ADNonPlayableCharacter* m_ControlledCharacter = nullptr;

	FTimerHandle UpdateAITimer;

	virtual void UpdateAI();

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	AGhoul_Ai_CON(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName PlayerKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName TargetKey;
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName LastSeenLocation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		FVector m_LastSeenLocation;
		
	//void SetPawnCaught(APawn* Pawn);

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

private:
	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//FVector m_AngleFromPlayer;
	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//FVector m_AngleFromAI;
	//FVector m_NormalizedVector;
	//UPROPERTY(EditDefaultsOnly, Category = "AI")
	//float IsOverZero;

	FVector m_InAttackRangeVector;
	float m_InAttackRangeFloat;
	float m_InAttackRange = 100.f;
	//float a;
	//float b;


	
	
};
