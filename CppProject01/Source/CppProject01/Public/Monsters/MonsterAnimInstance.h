// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT01_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		class ABaseMonster* Owner;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		class UCharacterMovementComponent* Movement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool IsFalling;

public:
	UFUNCTION()
		void AnimNotify_SetIsIdle();
};
