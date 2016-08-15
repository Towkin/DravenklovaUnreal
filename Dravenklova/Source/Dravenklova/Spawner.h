// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DObject.h"
#include "Spawner.generated.h"



UENUM(BlueprintType)
enum class ESpawnItem : uint8
{
	Humor = 0,
	Health = 1,
	Weapon = 2,
	Note = 3,
	Enemy = 4,
	Equipment = 5,
	END = 6
};

UCLASS()
class DRAVENKLOVA_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void OnConstruction(const FTransform& transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	bool Spawn(TSubclassOf<AActor> a_SpawnClass);	
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spawner")
	void DidNotSpawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool m_HasSpawned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	ESpawnItem m_TypeOfSpawner;

};
