// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "LevelBlock.generated.h"
/**
 * 
 */
/*UCLASS()
class DRAVENKLOVA_API ALevelBlock : public AActor
{
public:
};
*/
UENUM(BlueprintType)
enum class EDirection : uint8
{
	Forward = 0,
	Right = 1,
	Back = 2,
	Left = 3
};

UENUM(BlueprintType)
enum class EType : uint8
{
	Door = 0,	
	Fireplace = 1,
	Rathole = 2
};

UCLASS()
class AWall : public AActor
{
	GENERATED_BODY()
public:

};

UCLASS()
class AConnector : public AActor
{
	GENERATED_BODY()
public:
	EType Type;

};

USTRUCT(BlueprintType)
struct FPortalData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	FIntVector Location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	EDirection Direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TSubclassOf<AWall> WallType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TSubclassOf<AWall> PortalType;

	FPortalData* ConnectedPortal = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	bool IsPortal = false;
	bool IsExhausted = false;
	int LayerIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	EType Type;
};

USTRUCT(BlueprintType)
struct FBlockData
{
	GENERATED_BODY()
public:
	//UBlockData(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Portal")
	TArray<FPortalData> PortalArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tiles")
	FIntVector TileCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tiles")
	FVector TileSize;
		
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block")
	FIntVector BlockLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Block")
	EDirection BlockDirection;
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tiles")
	TArray<bool> OccupationGrid;

	TArray<FBlockData*> Neighbours;

	int Distance;
};


UCLASS()
class DRAVENKLOVA_API ABlock : public AActor
{
	GENERATED_BODY()
public:

	ABlock(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Block")
	//UBlockData* m_BlockData = nullptr;
	FBlockData m_BlockData;

	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Block")
	FIntVector GetLocalCoordinate(int Index) const;

	UFUNCTION(BlueprintCallable, Category = "Block")
	int GetLocalIndex(const FIntVector& Coordinate)const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Block")
	void SpawnBlockComponents();

	TArray<ABlock*> Neighbours;
	
};



