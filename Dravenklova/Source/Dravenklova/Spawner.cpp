// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "Spawner.h"



// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	m_HasSpawned = false;

}

void ASpawner::OnConstruction(const FTransform& transform)
{
	Super::OnConstruction(transform);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ASpawner::Spawn(TSubclassOf<AActor> a_SpawnClass)
{
	UWorld* world = GetWorld();
	if (world)
	{
		ADObject* item = world->SpawnActor<ADObject>(a_SpawnClass, this->GetActorLocation(), this->GetActorRotation());
		if (item != nullptr)
		{
			m_HasSpawned = true;
			return true;
		}
	}

	return false;
}

