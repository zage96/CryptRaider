// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle != nullptr){
		UE_LOG(LogTemp, Display, TEXT("Got Physics Handle: %s"),*PhysicsHandle->GetName());
	}
	else{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle Found!"));
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//FRotator MyRotation = GetComponentRotation();
	//FString MyRotationString = MyRotation.ToCompactString();
	//UE_LOG(LogTemp, Display, TEXT("Location Grabber: %s"),*MyRotationString);
	
	

	//UWorld* MyWorld = GetWorld();
	//float Time = MyWorld->TimeSeconds;
	//UE_LOG(LogTemp, Display, TEXT("Current Time is %f"), Time);



}


void UGrabber::Release(){
	UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
}

void UGrabber::Grab(){
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*MaxGrabDistance;
	DrawDebugLine(GetWorld(),Start,End, FColor::Red);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	FHitResult HitResult;

	//ECC_GameTraceChannel2 is hte name of the channel for Grabber, found on DefaultEngine.ini
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);
	
	if(HasHit){
		AActor* HitActor = HitResult.GetActor();
		UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *HitActor->GetActorNameOrLabel());
	}
	else{
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit"));
	}
}