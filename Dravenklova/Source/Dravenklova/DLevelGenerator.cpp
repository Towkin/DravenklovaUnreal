// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DLevelGenerator.h"
#include "LevelBlock.h"
//#include "Engine/Source/Runtime/AssetRegistry/Private/AssetRegistryModule.h"


// Sets default values
ADLevelGenerator::ADLevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FClassFinder<ABlock> block(TEXT("Blueprint'/Game/Dravenklova/Blueprints/Blocks/BP_Block'"));
	//UE_LOG(LogTemp, Warning, TEXT("Static constructorhelper"));

	m_BlockClass = block.Class;
	TArray<UObject*> blockAssets;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Dravenklova/Blueprints/Blocks/"), blockAssets, EngineUtils::ATL_Regular);

	int i = 0;
	for (TObjectIterator<UClass> blockIt; blockIt; ++blockIt)
	{
		if (blockIt->IsChildOf(m_BlockClass) && !blockIt->HasAnyClassFlags(CLASS_Abstract))
		{
			i++;
			m_BlockClasses.Emplace(*blockIt);
		}
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Number of block classes: %d"), i);

	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x1_01"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x2_01"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x2_02"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_6x4_01"
	m_TileCount = FIntVector(10, 10, 1);
	m_OccupationGrid.Init(false, 10 * 10);

}

// Called when the game starts or when spawned
void ADLevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	UWorld * const World = GetWorld();

	if (World)
	{
		//for(TSubclassOf<ABlock> blockClass : m_BlockClasses)
		//{
		//	World->SpawnActor<ABlock>(blockClass);
		//}

		//TODO: Check if block is null
		//TODO: Replace with starting block
		//Place starting block
		ABlock* block = World->SpawnActor<ABlock>(m_BlockClasses[3]);
		
		//Get world coordinates

		//Calculate grid coordinates
		block->m_BlockData.BlockLocation = FIntVector(3, 4, 0);
		
		//Occupy space in grid and reposition block in world space
		int blockIndex = GridToIndex(block->m_BlockData.BlockLocation);
		OccupyGrid(block, blockIndex);


		FPortalData portal = block->m_BlockData.PortalArray[0];
		portal.IsPortal = true;

		FIntVector modifier = FIntVector(0, 0, 0);
		switch (portal.Direction)
		{
		case EDirection::Forward:
			modifier.X += 1;
			break;
		case EDirection::Right:
			modifier.Y += 1;
			break;
		case EDirection::Back:
			modifier.X -= 1;
			break;
		case EDirection::Left:
			modifier.Y -= 1;
			break;
		default:
			break;
		}

		
		FIntVector wishedPortalTile = block->m_BlockData.BlockLocation + portal.Location + modifier;
		UE_LOG(LogTemp, Warning, TEXT("Modifier x,y: %d %d, mod"), modifier.X, modifier.Y);

		//Find all portals		
		//Choose one portal and find its direction, reverse it		
		EDirection wishedPortalDirection;
		
		int temp = ((int)portal.Direction + 2);
		while (temp > 3)
		{
			temp -= 3;
		}
		wishedPortalDirection = (EDirection)temp;
		
		//TODO: randomize block
		//TODO: check that block is not null
		//Spawn another block
		ABlock* otherBlock = World->SpawnActor<ABlock>(m_BlockClasses[2]);
		
		//Find corresponding portal in other block
		for (FPortalData otherPortal : block->m_BlockData.PortalArray)
		{
			if (wishedPortalDirection == otherPortal.Direction)
			{
				otherPortal.IsPortal = true;
				int indexValue = GridToIndex(wishedPortalTile) - GridToIndex(otherPortal.Location);

				//Position the other block next to the first one so that the portals can connect
				otherBlock->m_BlockData.BlockLocation = IndexToGrid(indexValue);

				//Mark the grid tiles as occupied
				OccupyGrid(otherBlock, indexValue);
				break;
			}		
		}

		

		//if not, rotate and repeat
		//if not successful, destroy and spawn new block, repeat

		//Lastly
		//Save block to array (TODO: create array)
		//copy otherBlock to block
		//Spawn new otherBlock

		UE_LOG(LogTemp, Warning, TEXT("SpawnActor"));
	}
	
}

// Called every frame
void ADLevelGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int ADLevelGenerator::GridToIndex(FIntVector gridLocation)
{
	int index = gridLocation.X + gridLocation.Y * m_TileCount.X + m_TileCount.X * m_TileCount.Y * gridLocation.Z;
	return index;
}

FIntVector ADLevelGenerator::IndexToGrid(int a_Index)
{
	FIntVector gridLocation = FIntVector::ZeroValue;

	if (m_TileCount.X == 0 || m_TileCount.Y == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Division by zero! in levelgenerator"))
			return gridLocation;
	}

	gridLocation.X = a_Index % m_TileCount.X;
	gridLocation.Y = (a_Index / m_TileCount.X) % m_TileCount.Y;
	gridLocation.Z = (a_Index / m_TileCount.X) / m_TileCount.Y;

	return gridLocation;
}

void ADLevelGenerator::OccupyGrid(ABlock* a_Block, int a_BlockIndex)
{
	for (int i = 0; i < a_Block->m_BlockData.OccupationGrid.Num(); i++)
	{
		if (a_Block->m_BlockData.OccupationGrid[i] == true)
		{
			m_OccupationGrid[a_BlockIndex + i] = true;
		}
	}

	a_Block->SetActorLocation(
		FVector(a_Block->m_BlockData.BlockLocation.X*a_Block->m_BlockData.TileSize.X,
			a_Block->m_BlockData.BlockLocation.Y*a_Block->m_BlockData.TileSize.Y,
			a_Block->m_BlockData.BlockLocation.Z*a_Block->m_BlockData.TileSize.Z));
}

