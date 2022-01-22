// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GGJ_CharacterController.generated.h"

UCLASS()

class GGJ_REFLECTION_API AGGJ_CharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGGJ_CharacterController();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool isJumping;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MyMeshComponent;

	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void HorizontalMove(float value);
	void VerticalMove(float value);
	
};
