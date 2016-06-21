// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "HalfVampire.h"


AHalfVampire::AHalfVampire()
{
}

AHalfVampire::~AHalfVampire()
{
}

void AHalfVampire::MoveForward(float a_Value)
{
	SetActorLocation(m_Speed * FVector(1, 0, 0) * a_Value);

}
