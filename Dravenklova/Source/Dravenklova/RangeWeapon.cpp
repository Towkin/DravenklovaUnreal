// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "RangeWeapon.h"


ARangeWeapon::ARangeWeapon(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}
const float ARangeWeapon::getAccuracy() const
{
	return m_Accuracy;
}
const float ARangeWeapon::getReloadTime() const
{
	return m_ReloadTime;
}
const float ARangeWeapon::getFireCooldownTime() const
{
	return m_FireCooldownTime;
}