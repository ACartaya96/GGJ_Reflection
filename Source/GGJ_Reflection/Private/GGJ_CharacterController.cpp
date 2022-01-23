
// Fill out your copyright notice in the Description page of Project Settings.


#include "GGJ_CharacterController.h"

// Sets default values
AGGJ_CharacterController::AGGJ_CharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 300.0f, 0.0f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowCamera->bUsePawnControlRotation = false;
	MySMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player"));
	MySMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	
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
	PlayerInputComponent-> BindAxis("Horizontal", this, &AGGJ_CharacterController::HorizontalMove);
	PlayerInputComponent-> BindAxis("Vertical", this, &AGGJ_CharacterController::VerticalMove);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AGGJ_CharacterController::HorizontalMove(float value)
{
	if (value && isClimbing == false)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void AGGJ_CharacterController::VerticalMove(float value)
{
	if (value  && isClimbing == false)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}


