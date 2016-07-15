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

	//static ConstructorHelpers::FClassFinder<ABlock> block(TEXT("Blueprint'/Game/Dravenklova/Blueprints/Blocks/BP_Block'"));
	//UE_LOG(LogTemp, Warning, TEXT("Static constructorhelper"));

	//m_BlockClass = block.Class;
	//TArray<UObject*> blockAssets;
	//EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/Dravenklova/Blueprints/Blocks/"), blockAssets, EngineUtils::ATL_Regular);

	//int i = 0;
	//for (TObjectIterator<UClass> blockIt; blockIt; ++blockIt)
	//{
	//	if (blockIt->IsChildOf(m_BlockClass) && !blockIt->HasAnyClassFlags(CLASS_Abstract))
	//	{
	//		i++;
	//		m_BlockClasses.Emplace(*blockIt);
	//	}
	//}
	//UE_LOG(LogTemp, Warning, TEXT("Number of block classes: %d"), i);

	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x1_01"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x2_01"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_2x2_02"
	//"Game/Dravenklova/Blueprints/Blocks/BP_Block_6x4_01"
	m_TileCount = FIntVector(20, 20, 1);
	m_OccupationGrid.Init(false, m_TileCount.X*m_TileCount.Y*m_TileCount.Z);

}

void ADLevelGenerator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	
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

		ABlock* block = World->SpawnActor<ABlock>(m_BlockClasses[2]);
		
		//Get world coordinates

		//Calculate grid coordinates
		block->m_BlockData.BlockLocation = FIntVector(10, 10, 0);
		
		//Occupy space in grid and reposition block in world space
		int blockIndex = GridToIndex(block->m_BlockData.BlockLocation, m_TileCount);
		//OccupyGrid(block, blockIndex);
		OccupyGrid(block->m_BlockData.BlockLocation, block->m_BlockData.OccupationGrid, block->m_BlockData.TileCount);
		PlaceBlockInWorld(block);

		FPortalData& portal = block->m_BlockData.PortalArray[0];
		portal.IsPortal = true;
		block->SpawnBlockComponents();

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
		
		int temp = ((int)portal.Direction + 2) % 4;

		wishedPortalDirection = (EDirection)temp;
		
		//TODO: randomize block
		//TODO: check that block is not null
		//Spawn another block
		ABlock* otherBlock = World->SpawnActor<ABlock>(m_BlockClasses[1]);
		

		bool foundPortal = false;
		for (int direction = 0; direction < 4 && !foundPortal; direction++)
		{
			//Find corresponding portal in other block
			for (FPortalData& otherPortal : otherBlock->m_BlockData.PortalArray)
			{
				if (wishedPortalDirection == otherPortal.Direction)
				{
					foundPortal = true;
					otherPortal.IsPortal = true;
					int indexValue = GridToIndex(wishedPortalTile - otherPortal.Location, m_TileCount);
					
					//Position the other block next to the first one so that the portals can connect
					otherBlock->m_BlockData.BlockLocation = IndexToGrid(indexValue, m_TileCount);
					
					if (m_ConnectorClasses.Num() > 0)
					{
						AConnector* connector = World->SpawnActor<AConnector>(m_ConnectorClasses[0]);

						FIntVector portalLocation = block->m_BlockData.BlockLocation + portal.Location;

						connector->SetActorLocation(FVector(portalLocation.X, portalLocation.Y, portalLocation.Z) * block->m_BlockData.TileSize);
						connector->SetActorRotation(FRotator(0, (int)portal.Direction * 90, 0));
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("No connectors found"));
					}
					
					//Mark the grid tiles as occupied
					//OccupyGrid(otherBlock, indexValue);
					OccupyGrid(otherBlock->m_BlockData.BlockLocation, otherBlock->m_BlockData.OccupationGrid, otherBlock->m_BlockData.TileCount);
					PlaceBlockInWorld(otherBlock);
					break;
				}
			}
			if (!foundPortal)
			{
				//Rotate block
				RotateBlock(*otherBlock);
			}	
		}
		


		otherBlock->SpawnBlockComponents();

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

int ADLevelGenerator::GridToIndex(FIntVector gridLocation, FIntVector a_TileCount)
{
	int index = gridLocation.X + gridLocation.Y * a_TileCount.X + a_TileCount.X * a_TileCount.Y * gridLocation.Z;
	return index;
}

FIntVector ADLevelGenerator::IndexToGrid(int a_Index, FIntVector a_TileCount)
{
	FIntVector gridLocation = FIntVector::ZeroValue;

	if (a_TileCount.X == 0 || a_TileCount.Y == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Division by zero! in levelgenerator"))
			return gridLocation;
	}

	gridLocation.X = a_Index % a_TileCount.X;
	gridLocation.Y = (a_Index / a_TileCount.X) % a_TileCount.Y;
	gridLocation.Z = (a_Index / a_TileCount.X) / a_TileCount.Y;

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

void ADLevelGenerator::OccupyGrid(FIntVector a_BlockLocation, TArray<bool> a_BlockGrid, FIntVector a_TileCount)
{
	for (int i = 0; i < a_BlockGrid.Num(); i++)
	{
		if (a_BlockGrid[i] == true)
		{
			FIntVector localCoord = IndexToGrid(i, a_TileCount);
			int globalIndex = GridToIndex(a_BlockLocation + localCoord, m_TileCount);
			m_OccupationGrid[globalIndex] = true;
		}
	}
}

void ADLevelGenerator::PlaceBlockInWorld(ABlock* a_Block)
{
	a_Block->SetActorLocation(
		FVector(a_Block->m_BlockData.BlockLocation.X*a_Block->m_BlockData.TileSize.X,
			a_Block->m_BlockData.BlockLocation.Y*a_Block->m_BlockData.TileSize.Y,
			a_Block->m_BlockData.BlockLocation.Z*a_Block->m_BlockData.TileSize.Z));
}

void ADLevelGenerator::RotateCoordinate(FIntVector& xy, FIntVector a_TileCount)
{
	int x = a_TileCount.Y - 1 -xy.Y;
	int y = xy.X;

	xy.X = x;
	xy.Y = y;
}

void ADLevelGenerator::RotateDirection(EDirection& a_Dir)
{
	int temp = ((int)a_Dir + 1) % 4;

	a_Dir = (EDirection)temp;
}

void ADLevelGenerator::RotateBounds(FIntVector& a_TileCount)
{
	int temp = a_TileCount.Y;
	a_TileCount.Y = a_TileCount.X;
	a_TileCount.X = temp;
}

void ADLevelGenerator::RotateGrid(TArray<bool>& a_Grid,FIntVector a_TileCount)
{
	TArray<bool> temp;

	temp.Init(false, a_Grid.Num());
	
	FIntVector newTileCount = FIntVector(a_TileCount.Y, a_TileCount.X, a_TileCount.Z);
	
	for (int i = 0; i < a_Grid.Num(); i++)
	{
		if (a_Grid[i])
		{
			FIntVector coord = IndexToGrid(i, a_TileCount);
			RotateCoordinate(coord, a_TileCount);
			int index = GridToIndex(coord, newTileCount);
			temp[index] = true;
		}
	}
		
	a_Grid = temp;
}

void ADLevelGenerator::RotateBlock(ABlock& a_Block)
{
	FBlockData blockData = a_Block.m_BlockData;

	for (FPortalData portal : blockData.PortalArray)
	{
		RotateCoordinate(portal.Location, blockData.TileCount);
		RotateDirection(portal.Direction);
	}
	RotateBounds(blockData.TileCount);
	RotateDirection(blockData.BlockDirection);
	RotateGrid(blockData.OccupationGrid, a_Block.m_BlockData.TileCount);

	a_Block.m_BlockData = blockData;
}


