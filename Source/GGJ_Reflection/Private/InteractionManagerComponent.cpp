// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractionManagerComponent.h"

#include "Interactable.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
#include "..\GGJ_Reflection.h"

// Sets default values for this component's properties
UInteractionManagerComponent::UInteractionManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UInteractionManagerComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	auto interaction = FindFirstInteraction();
	if (interaction != PreviousInteraction)
	{
		UObject* pold = PreviousInteraction.Get(false);
		if (pold)
		{
			IInteractable::Execute_ClearPreviewInteraction(pold);
		}
		UObject* pnew = interaction.Get(false);
		if (pnew)
		{
			IInteractable::Execute_PreviewInteraction(pnew);
		}
		PreviousInteraction = interaction;
	}
}

void UInteractionManagerComponent::DoInteraction()
{
	auto interaction = FindFirstInteraction();
	UObject* pinteraction = interaction.Get(false);
	if (pinteraction)
	{
		IInteractable::Execute_DoInteraction(pinteraction);
	}
}

TWeakObjectPtr<class AActor> UInteractionManagerComponent::FindFirstInteraction()
{
	ACharacter* powner = Cast<ACharacter>(GetOwner());
	auto pworld = powner ? powner->GetWorld() : nullptr;
	auto capsule = powner->FindComponentByClass<UCapsuleComponent>();

	auto start = capsule->GetComponentLocation();
	auto end = start + (capsule->GetComponentRotation().Vector() * Distance);
	float radius = capsule->GetScaledCapsuleHalfHeight() * CapsulePercent;
	//ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECC_Interactable);
	bool bTraceComplex = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(powner);
	TArray<FHitResult> OutHits;
	bool bIgnoreSelf = true;
	FLinearColor TraceColor = FLinearColor::Green;
	FLinearColor TraceHitColor = FLinearColor::Red;
	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	//ObjectTypes.Add(OBJ_Interactable);
	//TODO couldn't figure out how to find Interactable objects just define it in blueprint
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(pworld, start, end, radius, ObjectTypes, bTraceComplex, ActorsToIgnore, DrawDebugType, OutHits, bIgnoreSelf, TraceColor, TraceHitColor, DrawDebugTime))
	{
		for (auto& hit : OutHits)
		{
			if (hit.Actor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
			{
				return hit.Actor;
			}
		}
	}

	return nullptr;
}