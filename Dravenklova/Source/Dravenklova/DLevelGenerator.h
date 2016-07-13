// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DLevelGenerator.generated.h"

class ABlock;

UCLASS()
class DRAVENKLOVA_API ADLevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADLevelGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	TArray<ABlock*> m_Blocks;
	TArray<TSubclassOf<class ABlock>> m_BlockClasses;

	UPROPERTY()
	TSubclassOf<class ABlock> m_BlockClass;
	
};
