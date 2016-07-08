// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "FAttribute.h"
#include "DCharacter.h"
#include "DAttributes.h"



void FAttribute::UpdateAttribute(ADCharacter* pawn)
{
	float alpha = 0;
	for (EHumors humor : m_StatTypes)
	{
		switch (humor) 
		{
			case EHumors::Black: 
			{
				alpha += pawn->m_Attributes->getHumorBlack();
				break;
			}
			case EHumors::Yellow:
			{
				alpha += pawn->m_Attributes->getHumorYellow();
				break;

			}
			case EHumors::Red:
			{
				alpha += pawn->m_Attributes->getHumorRed();
				break;

			}
			case EHumors::White:
			{
				alpha += pawn->m_Attributes->getHumorWhite();
				break;

			}
			
		}
	}
	m_CurrentValue = FMath::Lerp(m_Value0, m_Value1, alpha);

}

float FAttribute::GetCurrentValue() const 
{
	return m_CurrentValue;
}
FAttribute::FAttribute(float A, float B, const TArray<EHumors>& Humors)
{
	m_Value0 = A;
	m_Value1 = B;
	m_StatTypes.Append(Humors);
}