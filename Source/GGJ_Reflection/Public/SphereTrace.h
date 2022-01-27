// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "SphereTrace.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GGJ_REFLECTION_API USphereTrace : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USphereTrace();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	
	USkeletalMeshComponent* Mesh;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere)
	FVector WallNormal = FVector(0,0,0);
	UPROPERTY(VisibleAnywhere)
	FVector WallLocation = FVector(0,0,0);
	UPROPERTY(VisibleAnywhere)
	FVector HeightLocation = FVector(0,0,0);
	UPROPERTY(EditAnywhere)
	float TraceRadius = 10.0f;
	UPROPERTY(EditAnywhere)
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType = EDrawDebugTrace::ForOneFrame;
	UPROPERTY(EditAnywhere)
	float DrawDebugTime = 2.0f;
	
	bool FrontTrace();

	bool HeightTrace();


};
