// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */

class Ghoul_Ai_CON;
UCLASS()
class DRAVENKLOVA_API ADNonPlayableCharacter : public ADCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	//AAICharacter();
	ADNonPlayableCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/* AI */
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FVector m_LastSeenLocation;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
		//UBoxComponent* m_Box;


	UPROPERTY(EditAnywhere, Category = "AI")
	bool HasLineOfSight = false;

protected:
	virtual void UpdateAttributes() override;
	
private:
	UFUNCTION()
		void OnPawnCaught(APawn* Pawn);

	
};
