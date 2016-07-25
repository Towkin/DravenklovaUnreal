// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DLevelGenerator.h"



// Sets default values
ADLevelGenerator::ADLevelGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Chnage this value in order to update the blueprint to use the value in OnConstruction ... This is stupid.
	m_TileCount = FIntVector(20, 10, 1);
	m_BlockNumberLimit = 6;
	m_BlockDepthLimit = 5;
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

	m_World = GetWorld();	

	if (m_World)
	{
		TArray<ABlock*> spawnedBlocks;
		//TODO: Check if block is null
		//TODO: Replace with starting block
		//Place starting block

		ABlock* startingBlock = m_World->SpawnActor<ABlock>(m_BlockClasses[0]);
		
		//Set world coordinates
		startingBlock->m_BlockData.BlockLocation = FIntVector(10, 10, 0);
		
		OccupyGrid(startingBlock);
		PlaceBlockInWorld(startingBlock);
		spawnedBlocks.Add(startingBlock);

		ABlock* previousBlock = startingBlock;	

		TArray<bool> triedIndices = TArray<bool>();
		triedIndices.Init(false, m_BlockClasses.Num());
		int randomInt = rand() % m_BlockClasses.Num();
		bool triedAll = false;


		//Spawn blocks from starting block to staircase
		while (spawnedBlocks.Num() < m_BlockDepthLimit && !triedAll) // while number of rooms is less than room limit		
		{	
			
			TSubclassOf<class ABlock> blockClass = m_BlockClasses[randomInt]; //change to randomizing function returning block class
			
			ABlock* nextBlock = SpawnNextBlock(blockClass, previousBlock);
			if (nextBlock != nullptr)
			{				
				spawnedBlocks.Add(nextBlock);
				previousBlock = nextBlock;
				triedAll = false;
				triedIndices = TArray<bool>();
				triedIndices.Init(false, m_BlockClasses.Num());
				//UE_LOG(LogTemp, Display, TEXT("Placed block: %d"), randomInt);
			}
			else
			{
				triedIndices[randomInt] = true;
				//UE_LOG(LogTemp, Display, TEXT("Failed to place block: %d"), randomInt);
			}

			randomInt = rand() % m_BlockClasses.Num();

			for (int i = 0; i < m_BlockClasses.Num() && triedIndices[randomInt]; i++)
			{
				randomInt = (randomInt + 1) % m_BlockClasses.Num();		
				if ((i == m_BlockClasses.Num() - 1) && triedIndices[randomInt])
				{
					triedAll = true;
					UE_LOG(LogTemp, Display, TEXT("Tried all block classes"));
				}
			}
		}
		UE_LOG(LogTemp, Display, TEXT("Number of blocks: %d"), spawnedBlocks.Num());
		
		for (ABlock* block : spawnedBlocks)
		{
			block->SpawnBlockComponents();
		}
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
	
	return index;
}

int ADLevelGenerator::LocalGridToIndex(FIntVector gridCoord, ABlock* a_Block)
{	
	int index = gridCoord.X + (gridCoord.Y * a_Block->m_BlockData.TileCount.X) + (gridCoord.Z * a_Block->m_BlockData.TileCount.X * a_Block->m_BlockData.TileCount.Y);
	
	return index;
}

FIntVector ADLevelGenerator::GlobalIndexToGrid(int a_Index)
{
	FIntVector gridLocation = FIntVector::ZeroValue;

	if (m_TileCount.X == 0 || m_TileCount.Y == 0) 
	{
		UE_LOG(LogTemp, Display, TEXT("Division by zero! in levelgenerator"))
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
	
	if (a_Block->m_BlockData.TileCount.X == 0 || a_Block->m_BlockData.TileCount.Y == 0) {
		UE_LOG(LogTemp, Display, TEXT("Division by zero! in levelgenerator"))
			return gridCoord;
	}

	gridCoord.X = a_Index % a_Block->m_BlockData.TileCount.X;
	gridCoord.Y = (a_Index / a_Block->m_BlockData.TileCount.X) % a_Block->m_BlockData.TileCount.Y;
	gridCoord.Z = (a_Index / a_Block->m_BlockData.TileCount.X) / a_Block->m_BlockData.TileCount.Y;

	RotateCoordinate(gridCoord, (int)a_Block->m_BlockData.BlockDirection);

	return gridCoord;
}

bool ADLevelGenerator::OccupyGrid(ABlock* a_Block)
{	
	TArray<int> indices;
	for (int i = 0; i < a_Block->m_BlockData.OccupationGrid.Num(); i++)
	{
		if (a_Block->m_BlockData.OccupationGrid[i] == true)
		{
			FIntVector localCoord = LocalIndexToGrid(i, a_Block);

			int globalIndex = GlobalGridToIndex(a_Block->m_BlockData.BlockLocation + localCoord);
			if (globalIndex > m_OccupationGrid.Num() || globalIndex < 0)
			{
				UE_LOG(LogTemp, Display, TEXT("Failed occupation"));
				return false;
			}
			indices.Add(globalIndex);			
		}
	}
	for(int index : indices)
	{
		m_OccupationGrid[index] = true;
	}
	return true;
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
			FIntVector location = a_Block->m_BlockData.BlockLocation + localCoord;
			if (location.X < 0 || location.Y < 0 || location.X > m_TileCount.X || location.Y > m_TileCount.Y )
			{				
				//UE_LOG(LogTemp, Display, TEXT("Block out of bounds : LevelGenerator::CheckUnoccupied"));
				return false;
			}
			int globalIndex = GlobalGridToIndex(a_Block->m_BlockData.BlockLocation + localCoord);

			//If occupied or out of bounds
			if (globalIndex > m_OccupationGrid.Num() || globalIndex < 0 || m_OccupationGrid[globalIndex] == true)
			{
				return false;
			}			
		}		
	}
	return true;
}

void ADLevelGenerator::SpawnConnector(ABlock* a_Block, FPortalData a_Portal)
{
	if (m_ConnectorClasses.Num() > 0)
	{
		FIntVector relativePortalLocation = a_Portal.Location;
		RotateCoordinate(relativePortalLocation, (int) a_Block->m_BlockData.BlockDirection);

		FIntVector portalLocation = a_Block->m_BlockData.BlockLocation + relativePortalLocation;

		AConnector* connector = m_World->SpawnActor<AConnector>(m_ConnectorClasses[0]);
		connector->SetActorLocation(FVector(portalLocation.X, portalLocation.Y, portalLocation.Z) * a_Block->m_BlockData.TileSize);
		connector->SetActorRotation(FRotator(0, (((int)a_Portal.Direction + (int)a_Block->m_BlockData.BlockDirection) % 4) * 90, 0));
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No connectors found"));
	}
}

ABlock* ADLevelGenerator::SpawnNextBlock(TSubclassOf<class ABlock> a_BlockClass, ABlock* a_PreviousBlock)
{
	ABlock* otherBlock = m_World->SpawnActor<ABlock>(a_BlockClass);

	for (FPortalData& portal : a_PreviousBlock->m_BlockData.PortalArray)
	{
		//FIntVector modifier = FIntVector(0, 0, 0);
		//
		////EDirection portalDirection = (EDirection)((int)portal.Direction + (int)a_PreviousBlock->m_BlockData.BlockDirection % 4);
		//
		//EDirection portalDirection = portal.Direction;
		//
		//switch (portalDirection)
		//{
		//case EDirection::Forward:
		//	modifier.X += 1;
		//	break;
		//case EDirection::Right:
		//	modifier.Y += 1;
		//	break;
		//case EDirection::Back:
		//	modifier.X -= 1;
		//	break;
		//case EDirection::Left:
		//	modifier.Y -= 1;
		//	break;
		//default:
		//	break;
		//}
		//
		//FIntVector portalLocation = portal.Location;
		//RotateCoordinate(portalLocation, (int)a_PreviousBlock->m_BlockData.BlockDirection);
		//
		//FIntVector suspectedTile = a_PreviousBlock->m_BlockData.BlockLocation + portalLocation + modifier;
		//FIntVector wishedPortalTile = a_PreviousBlock->m_BlockData.BlockLocation + portal.Location + modifier;
		//


		////Choose one portal and find its direction, reverse it		
		EDirection wishedPortalDirection = (EDirection)(((int)portal.Direction + (int)a_PreviousBlock->m_BlockData.BlockDirection + 2) % 4);
		
		//STEP ONE NEW SOLUTION
		FIntVector mod = FIntVector(1, 0, 0);
		RotateCoordinate(mod, (int)portal.Direction);
		FIntVector pLocMod = portal.Location + mod;
		RotateCoordinate(pLocMod, (int)a_PreviousBlock->m_BlockData.BlockDirection);
		FIntVector wT = a_PreviousBlock->m_BlockData.BlockLocation + pLocMod;

				
		bool foundPortal = false;
		for (int direction = 0; direction < 4 && !foundPortal; direction++)
		{
			//Find corresponding portal in other block
			//for (FPortalData& otherPortal : otherBlock->m_BlockData.PortalArray)
			for (int portalIndex = 0; portalIndex < otherBlock->m_BlockData.PortalArray.Num(); portalIndex++)
			{
				FPortalData& otherPortal = otherBlock->m_BlockData.PortalArray[portalIndex];
				int newPortalDirection = ((int)otherBlock->m_BlockData.BlockDirection + (int)otherPortal.Direction) % 4;
				//UE_LOG(LogTemp, Display, TEXT("New portal direction: %d"), newPortalDirection);
				if ((int)wishedPortalDirection == newPortalDirection)
				{

					//STEP TWO NEW SOLUTION
					FIntVector p2Loc = otherPortal.Location;
					
					//UE_LOG(LogTemp, Display, TEXT("wT: %d %d. b2Dir: %d. p2Loc: %d %d b2Bounds: %dx%d"), 
					//	(int)wT.X, (int)wT.Y, 
					//	(int)otherBlock->m_BlockData.BlockDirection,
					//	(int)p2Loc.X, (int)p2Loc.Y, 
					//	otherBlock->m_BlockData.TileCount.X, otherBlock->m_BlockData.TileCount.Y);

					RotateCoordinate(p2Loc, (int)otherBlock->m_BlockData.BlockDirection);
					FIntVector otherBlockTile = wT - p2Loc;

					

					//UE_LOG(LogTemp, Display, TEXT("Matched directions: %d %d"), (int)wishedPortalDirection, newPortalDirection);
					// Rotate the portal and position the portals next to each other
					//FIntVector RelativeLocalPortalLocation = otherPortal.Location;			
					//
					//RotateCoordinate(RelativeLocalPortalLocation, (int)otherBlock->m_BlockData.BlockDirection);	
					//
					//otherBlock->m_BlockData.BlockLocation = wishedPortalTile - RelativeLocalPortalLocation;
					//
					//FIntVector suspectedLocation = suspectedTile - RelativeLocalPortalLocation;

					//if (((int)a_PreviousBlock->m_BlockData.BlockDirection + (int)otherBlock->m_BlockData.BlockDirection) % 2 != 0)

					//if (((((int)portal.Direction + (int)a_PreviousBlock->m_BlockData.BlockDirection) % 4) == 0)
					//	&& (((int)otherPortal.Direction + (int)otherBlock->m_BlockData.BlockDirection) % 4) == 2
					//	&& otherBlock->m_BlockData.BlockLocation != suspectedLocation)
					//{
					//	//FIntVector portalLocation = portal.Location;
					//	//RotateCoordinate(portalLocation, (int)a_PreviousBlock->m_BlockData.BlockDirection);						
					//	//FIntVector suspectedTile = a_PreviousBlock->m_BlockData.BlockLocation + portalLocation + modifier;
					//	//FIntVector suspectedLocation = suspectedTile - RelativeLocalPortalLocation;
					//	//UE_LOG(LogTemp, Display, TEXT("%s %d %d should change to %d %d"), *otherBlock->GetName(),
					//	//	(int)otherBlock->m_BlockData.BlockLocation.X, (int)otherBlock->m_BlockData.BlockLocation.Y, 
					//	//	(int)suspectedLocation.X, (int)suspectedLocation.Y);
					//	//otherBlock->m_BlockData.BlockLocation = suspectedLocation;
					//}
					
					//if (otherBlock->m_BlockData.BlockLocation != otherBlockTile)
					//{
					//	UE_LOG(LogTemp, Display, TEXT("Moved block from %d %d to %d %d"),
					//		(int)otherBlock->m_BlockData.BlockLocation.X, (int)otherBlock->m_BlockData.BlockLocation.Y,
					//		(int)otherBlockTile.X, (int)otherBlockTile.Y);
					//}
					
					
					otherBlock->m_BlockData.BlockLocation = otherBlockTile;
					
					//Check that the location is clear to build on				
					if (CheckUnoccupied(otherBlock)) //&& not out of bounds
					{
						//if ((int)a_PreviousBlock->m_BlockData.BlockDirection != 0 && !(portalLocation.X == 0 && portalLocation.Y == 0 ))
						//if( (int)a_PreviousBlock->m_BlockData.BlockDirection != 0 
						//	&& a_PreviousBlock->m_BlockData.BlockDirection != otherBlock->m_BlockData.BlockDirection
						//	&& wishedPortalTile != a_PreviousBlock->m_BlockData.BlockLocation
						//	)

						//if(((((int)portal.Direction + (int)a_PreviousBlock->m_BlockData.BlockDirection) % 4) == 0) 
						//	&& (((int)otherPortal.Direction + (int)otherBlock->m_BlockData.BlockDirection) % 4) == 2)
						//{							
						//	UE_LOG(LogTemp, Display, TEXT("From %s: Block %d to %d, portal %d to %d, at %d %d / %d %d"), 
						//		*a_PreviousBlock->GetName(), 
						//		(int)a_PreviousBlock->m_BlockData.BlockDirection, (int)otherBlock->m_BlockData.BlockDirection,
						//		(int)portal.Direction, (int) otherPortal.Direction,
						//		portal.Location.X, portal.Location.Y, portalLocation.X, portalLocation.Y);
						//}

						//UE_LOG(LogTemp, Display, TEXT("Block is placeable"));
						SpawnConnector(a_PreviousBlock, portal);

						foundPortal = true;						
						portal.IsPortal = true;
						otherPortal.IsPortal = true;						

						//Mark the grid tiles as occupied and set actor location and rotation
						OccupyGrid(otherBlock);
						PlaceBlockInWorld(otherBlock);

						return otherBlock;
					}
					//UE_LOG(LogTemp, Display, TEXT("Trying to place block out of bounds at portal %d"), (int)otherPortal.Direction);
				}
			}
			if (!foundPortal)
			{
				//Rotatea_PreviousBlockdata used to fit portals
				RotateGrid(otherBlock);

				//UE_LOG(LogTemp, Display, TEXT("Rotating block: %d"), direction);
			}
		}
	}

	otherBlock->Destroy();
	UE_LOG(LogTemp, Display, TEXT("Destroying block"));

	return nullptr;
}
