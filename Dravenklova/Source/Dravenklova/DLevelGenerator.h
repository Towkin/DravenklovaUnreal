// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LevelBlock.h"
#include "DLevelGenerator.generated.h"

USTRUCT(BlueprintType)
struct FSpawnItem
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AActor> Item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int Value;
};

UCLASS()
class DRAVENKLOVA_API ADLevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADLevelGenerator(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_HumorItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_HealthItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_WeaponItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_NoteItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_EnemyItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	TArray<FSpawnItem> m_EquipmentItems;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_HumorLimitValue;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_HealthLimitValue;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_WeaponLimitValue;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_NoteLimitValue;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_EnemyLimitValue;

	UPROPERTY(EditAnywhere, BLueprintReadWrite, Category = "Spawner")
	int m_EquipmentLimitValue;

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

	bool CreateLevel(TSubclassOf<ABlock>& a_StartingBlockClass, FIntVector a_Location, TArray<FBlockData>& a_NewBlocks, TArray<TSubclassOf<ABlock>>& a_NewBlockTypes, TArray<TArray<int>>& a_NeighbourIndices);

	bool CreateStartingBlock(TSubclassOf<ABlock>& a_StartingBlockClass, FBlockData& a_NewBlock, FIntVector a_Location);

	int RandomiseBlockClassIndex(TArray<TSubclassOf<ABlock>>& a_BlockClasses, TArray<bool> triedIndices);

	UWorld* m_World;

	
};
