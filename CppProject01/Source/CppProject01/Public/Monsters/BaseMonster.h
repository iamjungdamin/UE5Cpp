// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UCLASS()
class CPPPROJECT01_API ABaseMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	float hp;
	float maxHp;

	float damage;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI Navigation")
		AActor* PatrolTarget;

	UPROPERTY(EditDefaultsOnly, Category = "AI Navigation")
		TArray<AActor*> PatrolTargets;
};