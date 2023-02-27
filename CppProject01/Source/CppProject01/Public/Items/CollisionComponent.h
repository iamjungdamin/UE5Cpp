// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionComponent.generated.h"

class UPrimitiveComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPPPROJECT01_API UCollisionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCollisionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool isCollisionEnabled = false;
	
	UPROPERTY()
		UPrimitiveComponent* CollisionMeshComp;

	UPROPERTY()
		TArray<AActor*> AlreadyHitActors;
	
	UPROPERTY()
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	UPROPERTY()
		TArray<AActor*> ActorsToIgnore;
	
	UPROPERTY()
		TArray<FHitResult> HitResults;

public:
	void SetCollisionMeshComp(UPrimitiveComponent* value);

private:
	FVector StartLoc;
	FVector EndLoc;
	float radius;

public:
	void EnableCollision();
	void DisableCollision();
	void ClearHitActors();

	void CollisionTrace();

	void AddActorsToIgnore(AActor* value);
	void RemoveActorsToIgnore(AActor* value);
};
