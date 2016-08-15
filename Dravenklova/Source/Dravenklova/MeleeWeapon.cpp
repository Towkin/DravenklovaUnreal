// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "MeleeWeapon.h"


AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

const float AMeleeWeapon::getMeleeDamage() const
{
	return m_MeleeDamage;
}
const float AMeleeWeapon::getMeleeCooldownTime() const
{
	return m_MeleeCooldownTime;
}