// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "OliveAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT01_API UOliveAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AOliveCharacter* OliveCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* Movement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;
};
