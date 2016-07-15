// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DLevelGenerator.generated.h"

class ABlock;
enum class EDirection : uint8;
UCLASS()
class DRAVENKLOVA_API ADLevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADLevelGenerator();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void OnConstruction(const FTransform& transform) override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	TArray<ABlock*> m_Blocks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<TSubclassOf<class ABlock>> m_BlockClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<TSubclassOf<class AConnector>> m_ConnectorClasses;

	void RotateCoordinate(FIntVector& xy, FIntVector a_TileCount);

	void RotateDirection(EDirection& a_Dir);

	void RotateBounds(FIntVector& a_TileCount);

	void RotateGrid(TArray<bool>& a_Grid, FIntVector a_TileCount);

	void RotateBlock(ABlock& a_Block);


	UPROPERTY()
	TSubclassOf<class ABlock> m_BlockClass;

	TArray<bool> m_OccupationGrid;
	FIntVector m_TileCount;

	int GridToIndex(FIntVector gridLocation, FIntVector a_TileCount);

	FIntVector IndexToGrid(int index, FIntVector a_TileCount);
	
	void OccupyGrid(ABlock* a_Block, int a_BlockIndex);

	void OccupyGrid(FIntVector a_BlockLocation, TArray<bool> a_BlockGrid, FIntVector a_TileCount);

	void PlaceBlockInWorld(ABlock* a_Block);
};
