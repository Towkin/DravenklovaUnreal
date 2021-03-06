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
	
	ADoor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void Interact(ADCharacter* pawn) override;
	virtual void EndInteract(ADCharacter* pawn) override;

public:

	UFUNCTION(BlueprintCallable, Category = "Door")
	float GetMaxAngle();
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	void SetMaxAngle(float a_Angle);
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	float GetMinAngle();
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	void SetMinAngle(float a_Angle);
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	float GetSpeed();
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	void SetSpeed(float a_Speed);
	
	UFUNCTION(BlueprintCallable, Category = "Door")
	bool IsOpen();


protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_Speed = 1.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MinAngle = 0.0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float m_MaxAngle = 90.0;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool m_IsOpen = false;

		float m_TargetAngle;


private:
	void OpenDoor();
	void CloseDoor();
	void MoveDoor(float a_DeltaTime, bool a_IsOpen);

	float m_PreviousAngle;
	//direction
	
	
};
