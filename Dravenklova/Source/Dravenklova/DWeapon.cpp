// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DWeapon.h"
#include "DCharacter.h"


void ADWeapon::Equip(ADCharacter* pawn)
{
	ReceiveEquipped(pawn);
	pawn->SetWeapon(this);
}
void ADWeapon::PrimaryActionBegin()
{
	OnPrimaryActionBegin();
}
void ADWeapon::PrimaryActionEnd()
{
	OnPrimaryActionEnd();
}
void ADWeapon::SecondaryActionBegin()
{
	OnSecondaryActionBegin();
}
void ADWeapon::SecondaryActionEnd()
{
	OnSecondaryActionEnd();
}
void ADWeapon::ReloadActionBegin()
{
	OnReloadActionBegin();
}
void ADWeapon::ReloadActionEnd()
{
	OnReloadActionEnd();
}
const float ADWeapon::getCharacterMoveSpeedMod()
{
	return m_CharacterMoveSpeedMod;
}
