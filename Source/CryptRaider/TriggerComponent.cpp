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

    //UE_LOG(LogTemp, Display, TEXT("Trigger Component is Ticking"));
	
}
