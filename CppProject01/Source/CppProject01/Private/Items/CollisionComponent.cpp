// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CollisionComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UCollisionComponent::UCollisionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCollisionComponent::BeginPlay()
{
	Super::BeginPlay();

	auto Pawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	ObjectTypes.Add(Pawn);
}


// Called every frame
void UCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (isCollisionEnabled) {
		CollisionTrace();
	}
}

void UCollisionComponent::SetCollisionMeshComp(UPrimitiveComponent* value)
{
	CollisionMeshComp = value;
}


void UCollisionComponent::EnableCollision()
{
	isCollisionEnabled = true;
	ClearHitActors();
}

void UCollisionComponent::DisableCollision()
{
	isCollisionEnabled = false;
}

void UCollisionComponent::ClearHitActors()
{
	AlreadyHitActors.Empty();
}

void UCollisionComponent::CollisionTrace()
{
	StartLoc = CollisionMeshComp->GetSocketLocation("CollisionStart");
	EndLoc = CollisionMeshComp->GetSocketLocation("CollisionEnd");
	radius = 20.f;

	bool result = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), StartLoc, EndLoc, radius,
		ObjectTypes, false, ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true
	);
	
	if (!result) {
		// 충돌 없으면 리턴
		return;
	}

	for (FHitResult& h : HitResults) {
		AActor* HitActor = h.GetActor();

		if (AlreadyHitActors.Contains(HitActor)) {
			// 이미 처리됐으면 리턴
			return;
		}

		AlreadyHitActors.Add(HitActor);
		
		//HitActor.OnHit();
	}
}

void UCollisionComponent::AddActorsToIgnore(AActor* value)
{
	ActorsToIgnore.AddUnique(value);
}

void UCollisionComponent::RemoveActorsToIgnore(AActor* value)
{
	ActorsToIgnore.Remove(value);
}

