// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "Dcharacter.h"
#include "DObject.h"


// Sets default values
ADObject::ADObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADObject::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void ADObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void ADObject::Interact(ADCharacter* pawn)
{
	ReceiveInteractBegin(pawn);
}
void ADObject::EndInteract(ADCharacter* pawn)
{
	ReceiveInteractEnd(pawn);
}
