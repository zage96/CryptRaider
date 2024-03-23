// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"


// Constructor
UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));
	// ...
	
}

// Called every frame
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (Mover == nullptr) {
		return;
	}  
	
    //UE_LOG(LogTemp, Display, TEXT("Trigger Component is Ticking"));
	AActor* Actor = GetAcceptableActor();
	if(Actor!= nullptr){
		//UE_LOG(LogTemp, Display, TEXT("UNLOCKING"));
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
		if(Component != nullptr){
			Component->SetSimulatePhysics(false);
		}
		Actor->AttachToComponent(this,FAttachmentTransformRules::KeepWorldTransform);
		Mover->SetShouldMove(true);
	}
	else{
		//UE_LOG(LogTemp, Display, TEXT("RELOCKING"));
		Mover->SetShouldMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover;
	return;
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);
	for (auto Actor:Actors){
		bool HasAcceptableTag = Actor->ActorHasTag(AcceptableActorTag);
		bool IsGrabbed = Actor->ActorHasTag("Grabbed");
		if(HasAcceptableTag && !IsGrabbed){
			return Actor;
		}
	}

	return nullptr;
}
