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
	
}

// Called when the game starts or when spawned
void ADLevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	UWorld * const World = GetWorld();

	if (World)
	{
		for(TSubclassOf<ABlock> blockClass : m_BlockClasses)
		{
			World->SpawnActor<ABlock>(blockClass);
		}
		
		UE_LOG(LogTemp, Warning, TEXT("SpawnActor"));
	}
	
}

// Called every frame
void ADLevelGenerator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

