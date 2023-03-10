// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/BaseEquipable.h"
#include "BaseWeapon.generated.h"

class UCollisionComponent;

/**
 * 
 */
UCLASS()
class CPPPROJECT01_API ABaseWeapon : public ABaseEquipable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		UCollisionComponent* CollisionComp;

protected:
	float damage;

public:
	FName HandSocketName;

public:
	virtual void OnEquipped() override;

	UCollisionComponent* GetCollisionComp() const;

	void SetDamge(int value);
	float GetDamage() const;
};
