// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseEquipable.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UStaticMeshComponent;

UCLASS()
class CPPPROJECT01_API ABaseEquipable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquipable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* ItemSkeletalMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* ItemStaticMesh;
	
	UPROPERTY(VisibleAnywhere)
		bool isEquipped = false;

public:
	virtual void OnEquipped();
	virtual void OnUnequipped();

	virtual void SetIsEquipped(bool value);
	virtual bool GetIsEquipped() const;

	void AttachActor(FName socketName);


};
