// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DLevelGenerator.h"
#include "Spawner.h"

// Sets default values
ADLevelGenerator::ADLevelGenerator(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Chnage this value in order to update the blueprint to use the value in OnConstruction ... This is stupid.
	m_TileCount = FIntVector(50, 50, 1);
	m_BlockNumberLimit = 8;
	m_BlockDepthLimit = 3;
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
	bool levelNotSpawned = true;
	TArray<FBlockData> spawnBlocks;
	TArray<FBlockData> pathBlocks;
	
	while (m_World && levelNotSpawned)
	{
		spawnBlocks.Empty();
		pathBlocks.Empty();
		TArray<TSubclassOf<ABlock>> blockTypes;
		TArray<TArray<int>> neighbourIndices;
		TArray<bool> triedIndices = TArray<bool>();
		triedIndices.Init(false, m_StartingBlockClasses.Num());
		bool triedAll = false;

		//|-----
		int randomInt = RandomiseBlockClassIndex(m_StartingBlockClasses, triedIndices);
		if (randomInt < 0)
		{
			triedAll = true;
		}

		TSubclassOf<ABlock> startingBlockClass = m_StartingBlockClasses[randomInt];
		FIntVector location = FIntVector(m_TileCount.X / 2, m_TileCount.Y / 2, 0);
		CreateLevel(startingBlockClass, location, spawnBlocks, blockTypes, neighbourIndices);
		
		//----|
		/*
		//TODO: Check if block is null
		//Choose block
		int randomInt = rand() % m_StartingBlockClasses.Num();
		FBlockData startingBlock = m_StartingBlockClasses[randomInt].GetDefaultObject()->m_BlockData;		
		//Set world coordinates
		startingBlock.BlockLocation = FIntVector(m_TileCount.X/2, m_TileCount.Y/2, 0);		
		OccupyGrid(startingBlock);
		//Add to lists
		spawnBlocks.Add(startingBlock);
		blockTypes.Add(m_StartingBlockClasses[randomInt]);
		neighbourIndices.Add(TArray<int>());
		*/
		//Reset control variables		
		//triedIndices.Empty();
		//triedIndices.Init(false, m_BlockClasses.Num());
		//randomInt = rand() % m_BlockClasses.Num();		
		
		//Spawn blocks from starting block to staircase
		/*
		while (spawnBlocks.Num() < m_BlockDepthLimit - 1 && !triedAll) // while number of rooms is less than room limit		
		{				
			//Choose block and set world coordinates
			TSubclassOf<class ABlock> blockClass = m_BlockClasses[randomInt]; 			
			FBlockData nextBlock;
			bool success = SpawnNextBlock(blockClass, nextBlock, spawnBlocks.Last());
			
			if (success) 
			{				
				//Add to lists
				spawnBlocks.Add(nextBlock);
				blockTypes.Add(blockClass);

				//Update list of connections between blocks
				neighbourIndices.Last().Add(neighbourIndices.Num());
				neighbourIndices.Add(TArray<int>());
				neighbourIndices.Last().Add(neighbourIndices.Num() - 2);

				//Reset control variables
				triedAll = false;
				triedIndices = TArray<bool>();
				triedIndices.Init(false, m_BlockClasses.Num());
				UE_LOG(LogTemp, Display, TEXT("Placed block: %s"), *m_BlockClasses[randomInt].GetDefaultObject()->GetName());
			}
			else
			{
				triedIndices[randomInt] = true;
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
		*/
		
		/*
		//Reset control variables
		FBlockData lastBlock;
		bool success = false;
		triedIndices = TArray<bool>();
		triedIndices.Init(false, m_StartingBlockClasses.Num());
		
		//Spawn staircase block - start over if not possible to place
		while (!success && !triedAll)
		{
			randomInt = rand() % m_StaircaseBlockClasses.Num();
			for (int i = 0; i < m_StaircaseBlockClasses.Num() && triedIndices[randomInt]; i++)
			{
				randomInt = (randomInt + 1) % m_StaircaseBlockClasses.Num();
				if ((i == m_StaircaseBlockClasses.Num() - 1) && triedIndices[randomInt])
				{
					triedAll = true;
					UE_LOG(LogTemp, Display, TEXT("Tried all block classes"));
				}
			}
			
			success = SpawnNextBlock(m_StaircaseBlockClasses[randomInt], lastBlock, spawnBlocks.Last());
			if (success)
			{			
				blockTypes.Add(m_StaircaseBlockClasses[randomInt]);
				spawnBlocks.Add(lastBlock);

				//Update list of connections between blocks
				neighbourIndices.Last().Add(neighbourIndices.Num());
				neighbourIndices.Add(TArray<int>());
				neighbourIndices.Last().Add(neighbourIndices.Num() - 2);

				break;
			}
			else
			{
				triedIndices[randomInt] = true;
			}
		}		

		UE_LOG(LogTemp, Display, TEXT("Last block: %s"), *blockTypes.Last().GetDefaultObject()->GetName());
		//If the last block could not be placed, start over from the beginning
		if (triedAll)
		{
			UE_LOG(LogTemp, Display, TEXT("Discarding blocks: %d"), spawnBlocks.Num());
			//Reset used variables - occupationgrid, spawnblocks etc.
			m_OccupationGrid.Empty();
			m_OccupationGrid.Init(false, m_TileCount.X*m_TileCount.Y*m_TileCount.Z);
			continue;
		}

		UE_LOG(LogTemp, Display, TEXT("Number of blocks from start to finish: %d"), spawnBlocks.Num());
		*/
		pathBlocks = spawnBlocks;		

		//Reset control variables
		TArray<bool> triedBlocks = TArray<bool>();
		triedBlocks.Init(false, pathBlocks.Num());
		triedIndices = TArray<bool>();
		triedIndices.Init(false, m_BlockClasses.Num());
		TArray<TArray<bool>> triedClassesArray = TArray<TArray<bool>>();
		triedClassesArray.Init(triedIndices, pathBlocks.Num());
		triedAll = false;

		//Spawn blocks surrounding the main path
		while (spawnBlocks.Num() < m_BlockNumberLimit && !triedAll)
		{		
			//If this is not changed through the for-loop, ie all blocks have been tried, the while-loop will end if the limit has been reached.
			triedAll = true;

			for (int blockIndex = 0; blockIndex < pathBlocks.Num(); blockIndex++)
			{
				if (triedBlocks[blockIndex])
				{			
					triedAll = true;
					continue;
				}
				else
				{
					triedAll = false;
				}				

				triedIndices = triedClassesArray[blockIndex];

				//Choose block and set world coordinates
				randomInt = rand() % m_BlockClasses.Num();							
				TSubclassOf<class ABlock> blockClass = m_BlockClasses[randomInt];
				FBlockData newBlock;
				bool success = SpawnNextBlock(blockClass, newBlock, pathBlocks[blockIndex]);
				if (success)
				{
					blockTypes.Add(blockClass);
					spawnBlocks.Add(newBlock);
					spawnBlocks[blockIndex] = pathBlocks[blockIndex];

					//Update list of connections between blocks
					neighbourIndices[blockIndex].Add(neighbourIndices.Num());
					neighbourIndices.Add(TArray<int>());
					neighbourIndices.Last().Add(blockIndex);
				}
				else
				{
					triedIndices[randomInt] = true;
				}

				randomInt = rand() % m_BlockClasses.Num();

				for (int i = 0; i < m_BlockClasses.Num() && triedIndices[randomInt]; i++)
				{
					randomInt = (randomInt + 1) % m_BlockClasses.Num();
					if ((i == m_BlockClasses.Num() - 1) && triedIndices[randomInt])
					{
						triedBlocks[blockIndex] = true;
					}
				}
				triedClassesArray[blockIndex] = triedIndices;
			}
			//If all blocks have been tried but there is not enough blocks, the list of blocks to try to make portals from is enlarged.
			if (triedAll && spawnBlocks.Num() > pathBlocks.Num())
			{
				TArray<bool> newIndices;
				newIndices.Init(false, spawnBlocks.Num() - pathBlocks.Num());
				triedBlocks.Append(newIndices);

				pathBlocks = spawnBlocks;

				//Reset control variables
				triedAll = false;				
				triedIndices = TArray<bool>();
				triedIndices.Init(false, m_BlockClasses.Num());
				triedClassesArray = TArray<TArray<bool>>();
				triedClassesArray.Init(triedIndices, pathBlocks.Num());

				UE_LOG(LogTemp, Display, TEXT("Adding a layer of blocks"));
			}
		}		
				
		UE_LOG(LogTemp, Display, TEXT("Total number of blocks in level: %d"), spawnBlocks.Num());
				
		for (int i = 0; i < spawnBlocks.Num(); i++)
		{
			FBlockData blockData = spawnBlocks[i];
			TSubclassOf<class ABlock> blockClass = blockTypes[i];

			FVector location = FVector(blockData.BlockLocation.X*blockData.TileSize.X,
				blockData.BlockLocation.Y*blockData.TileSize.Y,
				blockData.BlockLocation.Z*blockData.TileSize.Z);

			FRotator rotation = FRotator(0, (int)blockData.BlockDirection * 90, 0);

			ABlock* block = m_World->SpawnActor<ABlock>(blockClass, location, rotation);

			// TODO: Make sure block ALWAYS spawn. As of now, SpawnActor may return nullptr.
			if (block)
			{
				block->m_BlockData = blockData;

				block->SpawnBlockComponents();
				for (FPortalData& portal : block->m_BlockData.PortalArray)
				{
					if (portal.IsPortal && !portal.IsExhausted && portal.ConnectedPortal)
					{
						SpawnConnector(block->m_BlockData, portal);
						portal.IsExhausted = true;

						portal.ConnectedPortal->IsExhausted = true;
					}
				}
				m_Blocks.Add(block);
			}
		}
		//Add pointers to neighbouring blocks
		for( int j = 0; j < m_Blocks.Num(); j++)
		{
			for (int k = 0; k < neighbourIndices[j].Num(); k++)
			{
				m_Blocks[j]->Neighbours.Add(m_Blocks[k]);
			}
		}
		
		//////////////////////////////////////////
		//Here starts the part of the code responsible for spawning items and enemies in levels
		//////////////////////////////////////////
		TArray < TArray<ASpawner*>> spawners;
		int numberOfSpawners = (int)ESpawnItem::END;
		spawners.Init(TArray<ASpawner*>(), numberOfSpawners); //number of different types of spawners
		
		int tempLimit = 10;

		//Split the spawners into arrays depending on type
		for (TActorIterator<ASpawner> itr (GetWorld()); itr; ++itr)
		{
			spawners[(int)itr->m_TypeOfSpawner].Add(*itr);
		}

		//for each type
		//for each spawner
		//pick an item 
		//check that its value is less than the level limit
		//if so, subtract its value and spawn item

		int typeLimit = tempLimit;

		for (int i = 0; i < spawners.Num(); i++)
		{
			if (spawners[i].Num() != 0)
			{
				int randomValue = rand() % spawners[i].Num();
				for (int j = 0; j < spawners[i].Num() && typeLimit > 0; j++)
				{
					int k = (randomValue + j) % spawners[i].Num();
					ASpawner* itemSpawner = spawners[i][k];
					ESpawnItem item = itemSpawner->m_TypeOfSpawner;

					TArray<FSpawnItem>* itemArray;
					switch (item)
					{
					case ESpawnItem::Humor:
						itemArray = &m_HumorItems;
						break;

					case ESpawnItem::Health:
						itemArray = &m_HealthItems;
						break;

					case ESpawnItem::Weapon:
						itemArray = &m_WeaponItems;
						break;

					case ESpawnItem::Note:
						itemArray = &m_NoteItems;
						break;

					case ESpawnItem::Enemy:
						itemArray = &m_EnemyItems;
						break;

					case ESpawnItem::Equipment:
						itemArray = &m_EquipmentItems;
						break;

					default:
						itemArray = &m_EquipmentItems;
						UE_LOG(LogTemp, Warning, TEXT("Uninitialized itemArray in DLevelGenerator"));
						break;
					}

					if (itemArray->Num() != 0)
					{
						FSpawnItem randomItem = (*itemArray)[rand() % itemArray->Num()];
						if (randomItem.Value <= typeLimit)
						{
							if (!itemSpawner->Spawn(randomItem.Item))
							{
								itemSpawner->DidNotSpawn();
							}
							else
							{
								typeLimit -= randomItem.Value;
								itemSpawner->Destroy();
							}
						}
						else
						{
							itemSpawner->DidNotSpawn();
						}
					}
				}
			}
			
		}


		levelNotSpawned = false;
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

int ADLevelGenerator::LocalGridToIndex(FIntVector gridCoord, FBlockData& a_Block)
{	
	int index = gridCoord.X + (gridCoord.Y * a_Block.TileCount.X) + (gridCoord.Z * a_Block.TileCount.X * a_Block.TileCount.Y);
	
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

FIntVector ADLevelGenerator::LocalIndexToGrid(int a_Index, FBlockData& a_Block)
{
	FIntVector gridCoord = FIntVector::ZeroValue;
	
	if (a_Block.TileCount.X == 0 || a_Block.TileCount.Y == 0) {
		UE_LOG(LogTemp, Display, TEXT("Division by zero! in levelgenerator"))
			return gridCoord;
	}

	gridCoord.X = a_Index % a_Block.TileCount.X;
	gridCoord.Y = (a_Index / a_Block.TileCount.X) % a_Block.TileCount.Y;
	gridCoord.Z = (a_Index / a_Block.TileCount.X) / a_Block.TileCount.Y;

	RotateCoordinate(gridCoord, (int)a_Block.BlockDirection);

	return gridCoord;
}

bool ADLevelGenerator::OccupyGrid(FBlockData& a_Block)
{	
	TArray<int> indices;
	for (int i = 0; i < a_Block.OccupationGrid.Num(); i++)
	{
		if (a_Block.OccupationGrid[i] == true)
		{
			FIntVector localCoord = LocalIndexToGrid(i, a_Block);

			int globalIndex = GlobalGridToIndex(a_Block.BlockLocation + localCoord);
			if (globalIndex > m_OccupationGrid.Num() || globalIndex < 0)
			{
				//UE_LOG(LogTemp, Display, TEXT("Failed occupation : LevelGenerator::OccupyGrid"));
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

//void ADLevelGenerator::PlaceBlockInWorld(FBlock a_Block)
//{
//	a_Block->SetActorLocation(
//		FVector(a_Block->m_BlockData.BlockLocation.X*a_Block->m_BlockData.TileSize.X,
//			a_Block->m_BlockData.BlockLocation.Y*a_Block->m_BlockData.TileSize.Y,
//			a_Block->m_BlockData.BlockLocation.Z*a_Block->m_BlockData.TileSize.Z));
//	
//	a_Block->SetActorRotation(FRotator(0, (int)a_Block->m_BlockData.BlockDirection * 90, 0));
//	
//}

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

void ADLevelGenerator::RotateGrid(FBlockData& a_Block)
{	
	RotateDirection(a_Block.BlockDirection);	
}

bool ADLevelGenerator::CheckUnoccupied(FBlockData& a_Block)
{
	for (int index = 0; index < a_Block.OccupationGrid.Num(); index++)
	{
		if (a_Block.OccupationGrid[index])
		{
			FIntVector localCoord = LocalIndexToGrid(index, a_Block);
			FIntVector location = a_Block.BlockLocation + localCoord;
			if (location.X < 0 || location.Y < 0 || location.X > m_TileCount.X || location.Y > m_TileCount.Y )
			{				
				//UE_LOG(LogTemp, Display, TEXT("Block out of bounds : LevelGenerator::CheckUnoccupied"));
				return false;
			}
			int globalIndex = GlobalGridToIndex(a_Block.BlockLocation + localCoord);

			//If occupied or out of bounds
			if (globalIndex >= m_OccupationGrid.Num() || globalIndex < 0 || m_OccupationGrid[globalIndex] == true)
			{
				return false;
			}			
		}		
	}
	return true;
}

void ADLevelGenerator::SpawnConnector(FBlockData& a_Block, FPortalData a_Portal)
{
	if (m_ConnectorClasses.Num() > 0)
	{
		FIntVector relativePortalLocation = a_Portal.Location;
		RotateCoordinate(relativePortalLocation, (int) a_Block.BlockDirection);

		FIntVector portalLocation = a_Block.BlockLocation + relativePortalLocation;

		FVector location = FVector(portalLocation.X, portalLocation.Y, portalLocation.Z) * a_Block.TileSize;
		FRotator rotation = FRotator(0, (((int)a_Portal.Direction + (int)a_Block.BlockDirection) % 4) * 90, 0);
		AConnector* connector = m_World->SpawnActor<AConnector>(m_ConnectorClasses[0], location, rotation);
		
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("No connectors found"));
	}
}

bool ADLevelGenerator::SpawnNextBlock(TSubclassOf<class ABlock> a_BlockClass, FBlockData& a_NewBlock, FBlockData& a_PreviousBlock)
{
	FBlockData otherBlock = a_BlockClass.GetDefaultObject()->m_BlockData;

	int randomPortal = rand() % a_PreviousBlock.PortalArray.Num();
	//for (FPortalData& portal : a_PreviousBlock->m_BlockData.PortalArray)
	for (int i = 0; i < a_PreviousBlock.PortalArray.Num(); i++)
	{
		FPortalData& portal = a_PreviousBlock.PortalArray[(randomPortal + i) % a_PreviousBlock.PortalArray.Num()];
		////Choose one portal and find its direction, reverse it		
		EDirection wishedPortalDirection = (EDirection)(((int)portal.Direction + (int)a_PreviousBlock.BlockDirection + 2) % 4);

		//STEP ONE NEW SOLUTION
		//Find tile in front of current portal
		FIntVector mod = FIntVector(1, 0, 0);
		RotateCoordinate(mod, (int)portal.Direction);
		FIntVector pLocMod = portal.Location + mod;
		RotateCoordinate(pLocMod, (int)a_PreviousBlock.BlockDirection);
		FIntVector wT = a_PreviousBlock.BlockLocation + pLocMod;

		bool foundPortal = false;

		int randomDirection = rand() % 4;

		// Switched 'int i' - which was interfering with outer loop - to 'int j' /Emanuel - 16-08-08
		for (int j = 0; j < randomDirection; j++)
		{
			RotateGrid(otherBlock);
		}

		for (int direction = 0; direction < 4 && !foundPortal && !portal.IsPortal; direction++)
		{

			//Find corresponding portal in other block
			if (otherBlock.PortalArray.Num() == 0)
			{
				return false;
			}
			int randomInt = rand() % otherBlock.PortalArray.Num();
			for (int portalIndex = 0; portalIndex < otherBlock.PortalArray.Num(); portalIndex++)
			{
				FPortalData& otherPortal = otherBlock.PortalArray[(randomInt + portalIndex) % otherBlock.PortalArray.Num()];
				int newPortalDirection = ((int)otherBlock.BlockDirection + (int)otherPortal.Direction) % 4;

				if ((int)wishedPortalDirection == newPortalDirection && portal.PortalType == otherPortal.PortalType)
				{
					//STEP TWO NEW SOLUTION
					//Place the next block so that the portals are next to each other
					FIntVector p2Loc = otherPortal.Location;
					RotateCoordinate(p2Loc, (int)otherBlock.BlockDirection);
					otherBlock.BlockLocation = wT - p2Loc;

					//Check that the location is clear to build on				
					if (CheckUnoccupied(otherBlock))
					{
						//SpawnConnector(a_PreviousBlock, portal);

						foundPortal = true;
						portal.IsPortal = true;
						otherPortal.IsPortal = true;

						portal.ConnectedPortal = &otherPortal;
						otherPortal.ConnectedPortal = &portal;

						//if (!a_PreviousBlock.Neighbours.Contains(otherBlock))
						//{
						//	a_PreviousBlock.Neighbours.Add(&otherBlock);
						//}
						//if (!otherBlock.Neighbours.Contains(a_PreviousBlock))
						//{
						//	otherBlock.Neighbours.Add(&a_PreviousBlock);
						//}

						//Mark the grid tiles as occupied and set actor location and rotation
						OccupyGrid(otherBlock);

						a_NewBlock = otherBlock;
						a_NewBlock.BlockType = TArray<FString>();
						a_NewBlock.Neighbours = TArray<FBlockData*>();
						return true;
					}
				}
			}
			if (!foundPortal)
			{
				//Rotate block used to fit portals
				RotateGrid(otherBlock);
			}
		}
	}
	return false;
}

//Add blockClasses and staircaseClasses as arguments and replace the member variables used, in order to facilitate using different blocks for different levels
bool ADLevelGenerator::CreateLevel(TSubclassOf<ABlock>& a_StartingBlockClass, FIntVector a_Location, TArray<FBlockData>& a_NewBlocks, TArray<TSubclassOf<ABlock>>& a_NewBlockTypes, TArray<TArray<int>>& a_NeighbourIndices)
{
	bool levelNotDone = true;
	bool startNotDone = true;
	bool triedAll = false;
	TArray<bool> triedIndices;
	triedIndices.Init(false, m_BlockClasses.Num());
	TArray<TArray<bool>> triedIndicesArray;
	triedIndicesArray.Init(triedIndices, m_BlockDepthLimit);
	while (levelNotDone)
	{
		///////////////////////////////////
		//Spawn startingblock
		///////////////////////////////////
		FBlockData newBlock;
		if ( startNotDone && CreateStartingBlock(a_StartingBlockClass, newBlock, a_Location))
		{
			a_NewBlocks.Add(newBlock);
			a_NewBlockTypes.Add(a_StartingBlockClass);
			a_NeighbourIndices.Add(TArray<int>());
			startNotDone = false;
		}

		///////////////////////////////////
		//Spawn pathblocks
		///////////////////////////////////				
		while (a_NewBlocks.Num() < m_BlockDepthLimit && !triedAll) // while number of rooms is less than room limit		
		{			
			int randomInt = RandomiseBlockClassIndex(m_BlockClasses, triedIndices);

			if (randomInt < 0) //tried all blocks
			{
				//remove latest block and that all its connections are tried
				triedIndicesArray.Last().Empty(); 
				triedIndicesArray.Last().Init(false, m_BlockClasses.Num());				
				
				a_NewBlocks.RemoveAt(a_NewBlocks.Num() - 1);
				a_NewBlockTypes.RemoveAt(a_NewBlockTypes.Num() - 1);

				triedIndices = triedIndicesArray[a_NewBlocks.Num()];
				levelNotDone = true;

				// restart for previous block
				continue;
			}
			else
			{
				triedIndices[randomInt] = true;
			}

			//Choose block and set world coordinates
			TSubclassOf<class ABlock> blockClass = m_BlockClasses[randomInt];
			FBlockData nextBlock;
			if (SpawnNextBlock(blockClass, nextBlock, a_NewBlocks.Last()))
			{
				//Add to lists
				a_NewBlocks.Add(nextBlock);
				a_NewBlockTypes.Add(blockClass);

				//Update list of connections between blocks
				a_NeighbourIndices.Last().Add(a_NeighbourIndices.Num());
				a_NeighbourIndices.Add(TArray<int>());
				a_NeighbourIndices.Last().Add(a_NeighbourIndices.Num() - 2);

				//Reset control variables
				triedAll = false;
				triedIndicesArray[a_NewBlocks.Num() - 1] = triedIndices; //Save tried indices in case the next block has to be removed
				triedIndices.Empty();
				triedIndices.Init(false, m_BlockClasses.Num());
			}				
		}
				
		///////////////////////////////////
		//Spawn staircase block
		///////////////////////////////////		
		FBlockData lastBlock;
		triedIndices.Empty();
		triedIndices.Init(false, m_StaircaseBlockClasses.Num());

		//Spawn staircase block - start over if not possible to place
		while (!triedAll && a_NewBlocks.Num() >= m_BlockDepthLimit)
		{
			int randomInt = RandomiseBlockClassIndex(m_StaircaseBlockClasses, triedIndices);			
			if (randomInt < 0)
			{
				triedAll = true;
				break;
			}

			if (SpawnNextBlock(m_StaircaseBlockClasses[randomInt], lastBlock, a_NewBlocks.Last()))
			{
				a_NewBlockTypes.Add(m_StaircaseBlockClasses[randomInt]);
				a_NewBlocks.Add(lastBlock);

				//Update list of connections between blocks
				a_NeighbourIndices.Last().Add(a_NeighbourIndices.Num());
				a_NeighbourIndices.Add(TArray<int>());
				a_NeighbourIndices.Last().Add(a_NeighbourIndices.Num() - 2);
				levelNotDone = false;
				break;
			}
			else
			{
				triedIndices[randomInt] = true;
			}
		}

		//If the last block could not be placed, start over from the beginning. CHANGE THIS TO SOMETHING BETTER? Kinda did.
		if (triedAll && levelNotDone)
		{
			//TODO: clean neighbour indices array
			//Remove latest block and reset that block's tried connections
			if (a_NewBlocks.Num() > 1)
			{
				triedIndicesArray.Last().Empty();
				triedIndicesArray.Last().Init(false, m_BlockClasses.Num());

				a_NewBlocks.RemoveAt(a_NewBlocks.Num() - 1);
				a_NewBlockTypes.RemoveAt(a_NewBlockTypes.Num() - 1);

				triedIndices = triedIndicesArray[a_NewBlocks.Num() - 1];
				levelNotDone = true;
				triedAll = false;
				
			}
			else //If starting block needs to be removed, start over from the beginning of the level creation while-loop
			{
				startNotDone = true;
				levelNotDone = true;
				triedIndicesArray.Last().Empty();
				triedIndicesArray.Last().Init(false, m_BlockClasses.Num());

				a_NewBlocks.RemoveAt(a_NewBlocks.Num() - 1);
				a_NewBlockTypes.RemoveAt(a_NewBlockTypes.Num() - 1);
				UE_LOG(LogTemp, Warning, TEXT("Removing the start block"));
				a_NeighbourIndices.Empty();
				triedAll = false;
			}

			
			//Reset used variables - occupationgrid, spawnblocks etc.
			//m_OccupationGrid.Empty();
			//m_OccupationGrid.Init(false, m_TileCount.X*m_TileCount.Y*m_TileCount.Z);
			//continue;
		}
		else
		{
			levelNotDone = false;
		}		
	}

	return false;
}

bool ADLevelGenerator::CreateStartingBlock(TSubclassOf<ABlock>& a_StartingBlockClass, FBlockData& a_NewBlock, FIntVector a_Location)
{
	a_NewBlock= a_StartingBlockClass.GetDefaultObject()->m_BlockData;
	a_NewBlock.BlockLocation = a_Location;
	if (OccupyGrid(a_NewBlock))
	{
		return true;
	}
	return false;
}

int ADLevelGenerator::RandomiseBlockClassIndex(TArray<TSubclassOf<ABlock>>& a_BlockClasses, TArray<bool> a_TriedIndices)
{
	int randomInt = rand() % a_BlockClasses.Num();
	for (int i = 0; i < a_BlockClasses.Num() && a_TriedIndices[randomInt]; i++)
	{
		randomInt = (randomInt + 1) % a_BlockClasses.Num();
		if ((i == a_BlockClasses.Num() - 1 && a_TriedIndices[randomInt]))
		{
			return -1;
		}
	}
	return randomInt;
}