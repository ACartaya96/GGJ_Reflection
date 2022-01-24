// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereTrace.h"

// Sets default values for this component's properties
USphereTrace::USphereTrace()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USphereTrace::BeginPlay()
{
	Super::BeginPlay();

	// Store the start and end locations of the trace
	const FVector Start = GetOwner()->GetActorLocation();
	const FVector End = GetOwner()->GetActorLocation();
	//Array of actors to ignore
	TArray<AActor*>ActorsToIgnore;
	//Add Actor this is attached on to be ignored
	ActorsToIgnore.Add(GetOwner());
	//Variable to store the hit information return
	TArray<FHitResult> HitArray;

	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), Start, End, TraceRadius, UEngineTypes::ConvertToTraceType(ECC_Camera), false,
		ActorsToIgnore, EDrawDebugTrace::ForDuration, HitArray, true, FLinearColor::Red, FLinearColor::Green, 60.0f);

	//If we get a valid Hit
	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			//Print information to the screen about items we've hit
			GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Orange, 
				FString::Printf(TEXT("Hit: %s"), *HitResult.Actor->GetName()));
		}
	}
	
}


// Called every frame
void USphereTrace::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

