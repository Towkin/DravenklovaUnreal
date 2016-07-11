// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DWeapon.h"



void ADWeapon::BeginPrimaryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Primary"));
}
void ADWeapon::EndPrimaryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("End Primary"));
}
void ADWeapon::BeginSecondaryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Secondary"));
}
void ADWeapon::EndSecondaryAction()
{
	UE_LOG(LogTemp, Warning, TEXT("End Secondary"));
}
void ADWeapon::BeginReloadAction()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Reload"));
}
void ADWeapon::EndReloadAction()
{
	UE_LOG(LogTemp, Warning, TEXT("End Reload"));
}

