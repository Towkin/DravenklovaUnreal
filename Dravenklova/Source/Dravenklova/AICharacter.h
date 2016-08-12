// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DCharacter.h"
#include "AICharacter.generated.h"

/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API AAICharacter : public ADCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AAICharacter();

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
	
private:
	UFUNCTION()
		void OnPlayerCaught(APawn* Pawn);
	
};
