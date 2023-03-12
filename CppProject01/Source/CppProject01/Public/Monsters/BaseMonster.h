// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseMonster.generated.h"

UENUM(BlueprintType)
enum class ERangeType : uint8 {
	Narrow,
	Wide
};

UENUM(BlueprintType)
enum class EState : uint8 {
	NOTHING,
	PATROL,
	CHASE,
	ATTACK
};

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

private:
	bool isIdle = true;

protected:
	ERangeType rangeType = ERangeType::Narrow;
	
	float hp;
	float maxHp;

	float damage;

protected:
	virtual void SetMontages(FString folderPath, int count);

	UPROPERTY(EditDefaultsOnly, Category = Montages);
		TArray<UAnimMontage*> AttackMontages;

public:
	void SetIsIdle(bool value);
	bool GetIsIdle() const;

	ERangeType GetRangeType() const;

	void LoseHp(float amount);
	int GetHp() const;

	void Attack();
};
