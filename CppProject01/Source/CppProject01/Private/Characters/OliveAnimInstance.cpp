// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OliveAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOliveAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseCharacter>(TryGetPawnOwner());
	if (Owner) {
		Movement = Owner->GetCharacterMovement();
	}
}

void UOliveAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Movement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(Movement->Velocity);
		IsFalling = Movement->IsFalling();
	}
}

void UOliveAnimInstance::AnimNotify_SetIsIdle()
{
	Owner->SetIsIdle(true);
}

void UOliveAnimInstance::AnimNotify_SaveCombo()
{
	Owner->SaveCombo();
}

void UOliveAnimInstance::AnimNotify_ResetCombo()
{
	Owner->ResetCombo();
	Owner->SetIsIdle(true);
}

