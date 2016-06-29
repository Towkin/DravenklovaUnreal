// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DObject.h"
#include "Door.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class DRAVENKLOVA_API ADoor : public ADObject
{
	GENERATED_BODY()
		ADoor();

	virtual void Interact(ADCharacter* pawn) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=DoorMeshComponents)
		UStaticMeshComponent* m_Mesh;

private:

	void OpenDoor();
	void CloseDoor();
	//direction

	float m_Speed = 1.0;
	float m_MinAngle = 0.0;
	float m_MaxAngle = 180.0;
	bool m_IsOpen = false;
		
};
