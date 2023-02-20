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
	bool isCollisionEnabled = true;
	// todo: 디폴트 false, 공격 시에만 true
	
	UPROPERTY()
		UPrimitiveComponent* CollisionMeshComp;

	UPROPERTY()
		TArray<AActor*> AlreadyHitActors;

public:
	void SetCollisionMeshComp(UPrimitiveComponent* value);

private:
	FVector StartLoc;
	FVector EndLoc;
	float radius;

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> ActorsToIgnore;
	TArray<FHitResult> HitResults;

public:
	void EnableCollision();
	void DisableCollision();
	void ClearHitActors();

	void CollisionTrace();
};
