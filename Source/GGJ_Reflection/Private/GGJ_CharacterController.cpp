
// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_CharacterController.h"

// Sets default values
AGGJ_CharacterController::AGGJ_CharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	MyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder"));
	MyMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void AGGJ_CharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AGGJ_CharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGGJ_CharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent-> BindAxis("Horizontal", this, &AGGJ_CharacterController::HorizontalMove);
	InputComponent-> BindAxis("Vertical", this, &AGGJ_CharacterController::VerticalMove);
	
}

void AGGJ_CharacterController::HorizontalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AGGJ_CharacterController::VerticalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}


