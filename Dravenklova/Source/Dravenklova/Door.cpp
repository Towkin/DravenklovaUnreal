// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "Door.h"
#include "DCharacter.h"



ADoor::ADoor()
{
	
}

void ADoor::Interact(ADCharacter* pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("I'm a door"));
	if (m_IsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}

void ADoor::OpenDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door opens"));
	FRotator rotation;
	rotation.Yaw = 90.0f;
	rotation.Pitch = 0.0f;
	rotation.Roll = 0.0f;
	RootComponent->SetWorldRotation(rotation);

	m_IsOpen = true;
}

void ADoor::CloseDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door closes"));
	FRotator rotation;
	rotation.Yaw = 0.0f;
	rotation.Pitch = 0.0f;
	rotation.Roll = 0.0f;
	RootComponent->SetWorldRotation(rotation);

	m_IsOpen = false;
}


