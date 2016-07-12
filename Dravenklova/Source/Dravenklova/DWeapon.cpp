// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DWeapon.h"



void ADWeapon::PrimaryActionBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Primary"));
}
void ADWeapon::PrimaryActionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("End Primary"));
}
void ADWeapon::SecondaryActionBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Secondary"));
}
void ADWeapon::SecondaryActionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("End Secondary"));
}
void ADWeapon::ReloadActionBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Reload"));
}
void ADWeapon::ReloadActionEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("End Reload"));
}
const float ADWeapon::getCharacterMoveSpeedMod()
{
	return m_CharacterMoveSpeedMod;
}
