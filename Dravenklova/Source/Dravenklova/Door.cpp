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
	rotation.Yaw = m_MaxAngle;
	rotation.Pitch = 0.0f;
	rotation.Roll = 0.0f;
	RootComponent->SetWorldRotation(rotation);

	m_IsOpen = true;
}

void ADoor::CloseDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("Door closes"));
	FRotator rotation;
	rotation.Yaw = m_MinAngle;
	rotation.Pitch = 0.0f;
	rotation.Roll = 0.0f;
	RootComponent->SetWorldRotation(rotation);

	m_IsOpen = false;
}


float ADoor::GetMaxAngle()
{
	return m_MaxAngle;
}
	
void ADoor::SetMaxAngle(float a_Angle)
{
	m_MaxAngle = a_Angle;
}
	
float ADoor::GetMinAngle()
{
	return m_MinAngle;
}
	
void ADoor::SetMinAngle(float a_Angle)
{
	m_MinAngle = a_Angle;
}
	
float ADoor::GetSpeed()
{
	return m_Speed;
}
	
void ADoor::SetSpeed(float a_Speed)
{
	m_Speed = a_Speed;
}
	 
bool ADoor::IsOpen()
{
	return m_IsOpen;
}
