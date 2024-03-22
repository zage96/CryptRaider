// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


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

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr){
		return;
	}

	if(PhysicsHandle->GetGrabbedComponent() != nullptr){
		FVector TargetLocation = GetComponentLocation() + GetForwardVector()* HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	
}


void UGrabber::Release(){
	//UE_LOG(LogTemp, Display, TEXT("Released Grabber"));
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr)
		return;
	
	if(PhysicsHandle->GetGrabbedComponent() != nullptr){
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::Grab(){

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if(PhysicsHandle == nullptr){
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);
	
	if(HasHit){
		//DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 5);
		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 5);
		//AActor* HitActor = HitResult.GetActor();
		//UE_LOG(LogTemp, Display, TEXT("Hit Actor: %s"), *HitActor->GetActorNameOrLabel());
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();
		HitResult.GetActor()->Tags.Add("Grabbed");
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);

	}

}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(Result == nullptr){
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent."));
	}
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult)const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector()*MaxGrabDistance;
	DrawDebugLine(GetWorld(),Start,End, FColor::Red);
	DrawDebugSphere(GetWorld(),End,10,10,FColor::Blue,false,5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	//FHitResult HitResult;

	//"ECC_GameTraceChannel2" is the name of the channel for Grabber, found on DefaultEngine.ini
	bool HasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		Sphere
	);

	return HasHit;
}