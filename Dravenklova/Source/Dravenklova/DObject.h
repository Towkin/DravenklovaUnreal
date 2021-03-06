// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "DObject.generated.h"


UCLASS()
class DRAVENKLOVA_API ADObject : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADObject(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// IInteractInterface
	virtual void Interact(ADCharacter* pawn) override;
	
	virtual void EndInteract(ADCharacter* pawn) override;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interact")
	void ReceiveInteractBegin(ADCharacter* User);

	
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Interact")
	void ReceiveInteractEnd(ADCharacter* User);

};
