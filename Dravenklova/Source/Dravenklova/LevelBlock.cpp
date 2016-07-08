// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "LevelBlock.h"

//UBlockData::UBlockData(const FObjectInitializer& ObjectInitializer)
//	: Super(ObjectInitializer)
//{}

void ABlock::OnConstruction(const FTransform& Transform)
{
	//OccupationGrid.Init(false, TileCount.X * TileCount.Y * TileCount.Z);
	//m_BlockData->OccupationGrid.SetNum(m_BlockData->TileCount.X * m_BlockData->TileCount.Y * m_BlockData->TileCount.Z);
	m_BlockData.OccupationGrid.SetNum(m_BlockData.TileCount.X * m_BlockData.TileCount.Y * m_BlockData.TileCount.Z);

	UE_LOG(LogTemp, Warning, TEXT("ArraySize: %d"), m_BlockData.OccupationGrid.Num());
}

ABlock::ABlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//m_BlockData = CreateDefaultSubobject<UBlockData>(TEXT("BlockData"));

	//if (m_BlockData) 
	//{
	//	m_BlockData->TileCount = FIntVector::ZeroValue;
	//	m_BlockData->TileSize = FVector(200, 200, 300);
	//}

	m_BlockData.TileCount = FIntVector::ZeroValue;
	m_BlockData.TileSize = FVector(200, 200, 300);
}
