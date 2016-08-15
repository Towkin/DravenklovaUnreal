// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "Door.h"
#include "DCharacter.h"



ADoor::ADoor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	m_TargetAngle = GetActorRotation().Yaw;
	m_PreviousAngle = m_TargetAngle;
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	float currentAngle = GetActorRotation().Yaw;

	if ((IsOpen() &&  currentAngle < m_TargetAngle) || (!IsOpen() && currentAngle > m_TargetAngle))
	{
		MoveDoor(DeltaTime, IsOpen());

		//TODO: register collisions and stop movement if blocked by something
	}
}

void ADoor::Interact(ADCharacter* pawn)
{
	Super::Interact(pawn);

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
void ADoor::EndInteract(ADCharacter* pawn)
{
	Super::EndInteract(pawn);
}

void ADoor::OpenDoor()
{
	m_IsOpen = true;

	m_TargetAngle = m_MaxAngle;

	int yaw = GetActorRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("Open door: %d"), yaw);
}

void ADoor::CloseDoor()
{
	m_IsOpen = false;

	m_TargetAngle = m_MinAngle;

	int yaw = GetActorRotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("Close door: %d"), yaw);
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

void ADoor::MoveDoor(float a_DeltaTime, bool a_IsOpen)
{
	//Move towards target angle
	
	// Calculate change in rotation this frame
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Yaw = m_Speed * a_DeltaTime;

	if (!a_IsOpen)
	{
		DeltaRotation.Yaw = -DeltaRotation.Yaw;
	}

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);
}
