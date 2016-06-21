// Fill out your copyright notice in the Description page of Project Settings.

#include "Dravenklova.h"
#include "DPawn.h"

// Sets default values
ADPawn::ADPawn()
{

	MyCameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));

	//MyCameraSpringArm->AttachTo(RootComponent);
	MyCameraSpringArm->SetupAttachment(RootComponent);

	//Rotate camera when pawn does
	MyCameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));

	MyCameraSpringArm->TargetArmLength = 400.f;

	//MyCameraSpringArm->bEnableCameraLag = true;
	//MyCameraSpringArm->CameraLagSpeed = 3.0f;

	//Create a camera
	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));

	//MyCamera->AttachTo(MyCameraSpringArm, USpringArmComponent::SocketName);
	MyCamera->SetupAttachment(MyCameraSpringArm, USpringArmComponent::SocketName);

	//Take control of the default Player
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	//RootComponent = MyCameraSpringArm;
	
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera spring arm
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	m_Speed = 2;

}

// Called when the game starts or when spawned
void ADPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
//void ADPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
//{
//	Super::SetupPlayerInputComponent(InputComponent);
//
//}

void ADPawn::MoveForward(float a_Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Pawn on the move"));
	this->SetActorLocation(this->GetActorLocation() + FVector(m_Speed, 0, 0) * a_Value);
}

