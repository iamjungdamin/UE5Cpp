// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/MonsterAnimInstance.h"
#include "Monsters/BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ABaseMonster>(TryGetPawnOwner());
	if (Owner) {
		Movement = Owner->GetCharacterMovement();
	}
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Movement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(Movement->Velocity);
		IsFalling = Movement->IsFalling();
	}
}

void UMonsterAnimInstance::AnimNotify_SetIsIdle()
{
	Owner->SetIsIdle(true);
}

