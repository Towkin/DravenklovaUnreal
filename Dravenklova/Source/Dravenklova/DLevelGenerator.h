// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelBlock.h"
#include "DLevelGenerator.generated.h"

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
	TArray<TSubclassOf<class ABlock>> m_StartingBlockClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<TSubclassOf<class ABlock>> m_StaircaseBlockClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<TSubclassOf<class ABlock>> m_BlockClasses;

	UPROPERTY(BlueprintReadWrite)
	int m_BlockNumberLimit;
	UPROPERTY(BlueprintReadWrite)
	int m_BlockDepthLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	TArray<TSubclassOf<class AConnector>> m_ConnectorClasses;

	void RotateCoordinate(FIntVector& xy, int a_RotationSteps);

	void RotateDirection(EDirection& a_Dir);

	void RotateBounds(FIntVector& a_TileCount);

	void RotateGrid(FBlockData& a_Block);
	
	UPROPERTY()
	TSubclassOf<class ABlock> m_BlockClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<bool> m_OccupationGrid;

	UPROPERTY(BlueprintReadWrite)
	FIntVector m_TileCount;

	UFUNCTION(BlueprintCallable, Category = "Level")
	int GlobalGridToIndex(FIntVector gridCoord);
	
	UFUNCTION(BlueprintCallable, Category = "Level")
	int LocalGridToIndex(FIntVector gridCoord, FBlockData& a_Block);

	UFUNCTION(BlueprintCallable, Category = "Level")
	FIntVector GlobalIndexToGrid(int index);
	UFUNCTION(BlueprintCallable, Category = "Level")
	FIntVector LocalIndexToGrid(int index, FBlockData& a_Block);
	
	bool OccupyGrid(FBlockData& a_Block);

	//void PlaceBlockInWorld(ABlock& a_Block);

	bool CheckUnoccupied(FBlockData& a_Block);

	void SpawnConnector(FBlockData& a_Block, FPortalData a_Portal);

	bool SpawnNextBlock(TSubclassOf<class ABlock> a_BlockClass, FBlockData& a_NewBlock, FBlockData& a_PreviousBlock);

	UWorld* m_World;

	
};
