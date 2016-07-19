// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DLevelGenerator.h"
#include "LevelBlock.h"


// Sets default values
ADLevelGenerator::ADLevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Chnage this value in order to update the blueprint to use the value in OnConstruction ... This is stupid.
	m_TileCount = FIntVector(20, 10, 1);
	m_OccupationGrid.Init(false, m_TileCount.X*m_TileCount.Y*m_TileCount.Z);

}

void ADLevelGenerator::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);

	m_TileCount = FIntVector(50, 50, 1);
	m_OccupationGrid.Init(false, m_TileCount.X*m_TileCount.Y*m_TileCount.Z);
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

		ABlock* block = World->SpawnActor<ABlock>(m_BlockClasses[0]);
		
		//Get world coordinates

		//Calculate grid coordinates
		block->m_BlockData.BlockLocation = FIntVector(5, 5, 0);
		
		//Occupy space in grid and reposition block in world space
		int blockIndex = GlobalGridToIndex(block->m_BlockData.BlockLocation);		
		
		OccupyGrid(block);

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

		//Find all portals		
		//Choose one portal and find its direction, reverse it		
		EDirection wishedPortalDirection;
		
		int temp = ((int)portal.Direction + (int)block->m_BlockData.BlockDirection + 2) % 4;

		wishedPortalDirection = (EDirection)temp;
		
		//TODO: randomize block
		//TODO: check that block is not null
		//Spawn another block
		ABlock* otherBlock = World->SpawnActor<ABlock>(m_BlockClasses[1]);
		
		bool foundPortal = false;
		for (int direction = 0; direction < 4  && !foundPortal; direction++)
		{
		
			//Find corresponding portal in other block
			for (FPortalData& otherPortal : otherBlock->m_BlockData.PortalArray)
			{
				if ((int)wishedPortalDirection == ((int)otherBlock->m_BlockData.BlockDirection + (int)otherPortal.Direction) % 4) 
				{
					// Rotate the portal's local block-location
					FIntVector RelativeLocalPortalLocation = otherPortal.Location;
					for (int i = 0; i < (int)otherBlock->m_BlockData.BlockDirection; i++)
					{
						RotateCoordinate(RelativeLocalPortalLocation, 1);
					}
		
					// Find the index of where the block should be placed globally
					int blockIndexValue = GlobalGridToIndex(wishedPortalTile - RelativeLocalPortalLocation);
		
					//Position the other block next to the first one so that the portals can connect
					FIntVector blockLocation = GlobalIndexToGrid(blockIndexValue);
		
					//Check that the location is clear to build on
					if (direction > 2)
					{
						if (CheckUnoccupied(otherBlock)) //&& not out of bounds
						{
							otherBlock->m_BlockData.BlockLocation = blockLocation;
		
							foundPortal = true;
							otherPortal.IsPortal = true;
		
		
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
							OccupyGrid(otherBlock);
							PlaceBlockInWorld(otherBlock);
							break;
						}
						else
						{
							UE_LOG(LogTemp, Warning, TEXT("Grid is occupied"));
						}
					}
				}
				//UE_LOG(LogTemp, Warning, TEXT("Rotating Portal: %d"), (int)otherPortal.Direction);
			}
			if (!foundPortal)
			{
				//Rotate blockdata used to fit portals
				RotateGrid(otherBlock);
		
				UE_LOG(LogTemp, Warning, TEXT("Rotating Block: %d"), direction);
			}	
		}
		//TODO:
		//if suitable portal not found,
		//delete block and spawn new
		//Repeat process


		//after end loop
		//If no suitable block is found, mark portal as closed

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

int ADLevelGenerator::GlobalGridToIndex(FIntVector gridCoord)
{
	int index = gridCoord.X + (gridCoord.Y * m_TileCount.X) + (gridCoord.Z * m_TileCount.X * m_TileCount.Y);
	if (index < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Index below zero!: Levelgenerator::GlobalGridToIndex"))
		return 0;
	}
	return index;
}

int ADLevelGenerator::LocalGridToIndex(FIntVector gridCoord, ABlock* a_Block)
{	
	FIntVector rotatedTileCount = a_Block->m_BlockData.TileCount;	

	int index = gridCoord.X + (gridCoord.Y * rotatedTileCount.X) + (gridCoord.Z * rotatedTileCount.X * rotatedTileCount.Y);
	if (index < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Index below zero! in levelgenerator"))
			return 0;
	}
	return index;
}

FIntVector ADLevelGenerator::GlobalIndexToGrid(int a_Index)
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

FIntVector ADLevelGenerator::LocalIndexToGrid(int a_Index, ABlock* a_Block)
{
	FIntVector gridCoord = FIntVector::ZeroValue;
	FIntVector rotatedTileCount = a_Block->m_BlockData.TileCount;
	
	if (a_Block->m_BlockData.TileCount.X == 0 || a_Block->m_BlockData.TileCount.Y == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Division by zero! in levelgenerator"))
			return gridCoord;
	}

	gridCoord.X = a_Index % rotatedTileCount.X;
	gridCoord.Y = (a_Index / rotatedTileCount.X) % rotatedTileCount.Y;
	gridCoord.Z = (a_Index / rotatedTileCount.X) / rotatedTileCount.Y;

	RotateCoordinate(gridCoord, (int)a_Block->m_BlockData.BlockDirection);

	return gridCoord;
}

void ADLevelGenerator::OccupyGrid(ABlock* a_Block)
{	
	for (int i = 0; i < a_Block->m_BlockData.OccupationGrid.Num(); i++)
	{
		if (a_Block->m_BlockData.OccupationGrid[i] == true)
		{
			FIntVector localCoord = LocalIndexToGrid(i, a_Block);

			int globalIndex = GlobalGridToIndex(a_Block->m_BlockData.BlockLocation + localCoord);
			if (globalIndex > m_OccupationGrid.Num())
			{
				globalIndex -= m_OccupationGrid.Num() * 3 / 4;
				UE_LOG(LogTemp, Warning, TEXT("globalIndex out of bounds: LevelGenerator::OccupyGrid"));
			}
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

void ADLevelGenerator::RotateCoordinate(FIntVector& xy, int a_RotationSteps)
{
	for (int i = 0; i < a_RotationSteps; i++)
	{
		int x = -xy.Y;
		int y = xy.X;

		xy.X = x;
		xy.Y = y;
	}
	
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

void ADLevelGenerator::RotateGrid(ABlock* a_Block)
{	
	RotateDirection(a_Block->m_BlockData.BlockDirection);	
}

bool ADLevelGenerator::CheckUnoccupied(ABlock* a_Block)
{
	for (int index = 0; index < a_Block->m_BlockData.OccupationGrid.Num(); index++)
	{
		if (a_Block->m_BlockData.OccupationGrid[index])
		{
			FIntVector localCoord = LocalIndexToGrid(index, a_Block);

			int globalIndex = GlobalGridToIndex(a_Block->m_BlockData.BlockLocation + localCoord);
			if (globalIndex > m_OccupationGrid.Num())
			{
				globalIndex -= m_OccupationGrid.Num() * 3 / 4;
				UE_LOG(LogTemp, Warning, TEXT("globalIndex out of bounds: LevelGenerator::CheckUnoccupied"));
			}
			if (m_OccupationGrid[globalIndex] == true)
			{
				return false;
			}


			//FIntVector globalCoords = LocalIndexToGrid(index, a_Block) + a_Block->m_BlockData.BlockLocation;
			//int gridIndex = GlobalGridToIndex(globalCoords);
			//if (m_OccupationGrid[gridIndex])
			//{
			//	return false;
			//}
		}
		
	}
	return true;
}





