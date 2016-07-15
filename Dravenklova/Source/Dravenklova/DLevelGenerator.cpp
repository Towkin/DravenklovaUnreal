// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DLevelGenerator.h"
#include "LevelBlock.h"


// Sets default values
ADLevelGenerator::ADLevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
		//TODO: Check if block is null
		//TODO: Replace with starting block
		//Place starting block

		ABlock* block = World->SpawnActor<ABlock>(m_BlockClasses[1]);
		
		//Get world coordinates

		//Calculate grid coordinates
		block->m_BlockData.BlockLocation = FIntVector(10, 10, 0);
		
		//Occupy space in grid and reposition block in world space
		int blockIndex = GridToIndex(block->m_BlockData.BlockLocation, m_TileCount);
		
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
		//UE_LOG(LogTemp, Warning, TEXT("Modifier x,y: %d %d, mod"), modifier.X, modifier.Y);

		//Find all portals		
		//Choose one portal and find its direction, reverse it		
		EDirection wishedPortalDirection;
		
		int temp = ((int)portal.Direction + (int)block->m_BlockData.BlockDirection + 2) % 4;

		wishedPortalDirection = (EDirection)temp;
		
		//TODO: randomize block
		//TODO: check that block is not null
		//Spawn another block
		ABlock* otherBlock = World->SpawnActor<ABlock>(m_BlockClasses[5]);
		

		bool foundPortal = false;
		for (int direction = 0; direction < 4 && !foundPortal; direction++)
		{
			//Find corresponding portal in other block
			for (FPortalData& otherPortal : otherBlock->m_BlockData.PortalArray)
			{
				if ((int)wishedPortalDirection == ((int)otherBlock->m_BlockData.BlockDirection + (int)otherPortal.Direction) % 4)
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
						connector->SetActorRotation(FRotator(0, (((int)portal.Direction + (int)block->m_BlockData.BlockDirection) % 4) * 90, 0));
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("No connectors found"));
					}
					
					//Mark the grid tiles as occupied and set actor location and rotation
					OccupyGrid(otherBlock->m_BlockData.BlockLocation, otherBlock->m_BlockData.OccupationGrid, otherBlock->m_BlockData.TileCount);
					PlaceBlockInWorld(otherBlock);
					break;
				}
				//UE_LOG(LogTemp, Warning, TEXT("Rotating Portal: %d"), (int)otherPortal.Direction);
			}
			if (!foundPortal)
			{
				//Rotate blockdata used to fit portals
				RotateGrid(otherBlock->m_BlockData);

				UE_LOG(LogTemp, Warning, TEXT("Rotating Block: %d"), direction);
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


void ADLevelGenerator::OccupyGrid(FIntVector a_BlockLocation, TArray<bool> a_BlockGrid, FIntVector a_TileCount)
{
	FIntVector tileCount = FIntVector(a_TileCount.Y, a_TileCount.X, a_TileCount.Z);
	for (int i = 0; i < a_BlockGrid.Num(); i++)
	{
		if (a_BlockGrid[i] == true)
		{
			FIntVector localCoord = IndexToGrid(i, tileCount);
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
	
	a_Block->SetActorRotation(FRotator(0, (int)a_Block->m_BlockData.BlockDirection * 90, 0));
	
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

	//UE_LOG(LogTemp, Warning, TEXT("a_Dir change: %d to % d"), (int)a_Dir, temp);
	a_Dir = (EDirection)temp;
}

void ADLevelGenerator::RotateBounds(FIntVector& a_TileCount)
{
	int temp = a_TileCount.Y;
	a_TileCount.Y = a_TileCount.X;
	a_TileCount.X = temp;
}

void ADLevelGenerator::RotateGrid(FBlockData& a_BlockData)
{
	TArray<bool> temp;
	temp.Init(false, a_BlockData.OccupationGrid.Num());
	
	FIntVector newTileCount = FIntVector(a_BlockData.TileCount.Y, a_BlockData.TileCount.X, a_BlockData.TileCount.Z);
	
	for (int i = 0; i < a_BlockData.OccupationGrid.Num(); i++)
	{
		if (a_BlockData.OccupationGrid[i])
		{
			FIntVector coord = IndexToGrid(i, a_BlockData.TileCount);
			RotateCoordinate(coord, a_BlockData.TileCount);
			int index = GridToIndex(coord, newTileCount);
			temp[index] = true;
		}
	}

	RotateDirection(a_BlockData.BlockDirection);

	a_BlockData.OccupationGrid = temp;
}




