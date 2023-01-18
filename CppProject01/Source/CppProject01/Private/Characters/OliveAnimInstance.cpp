// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OliveAnimInstance.h"
#include "Characters/OliveCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UOliveAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OliveCharacter = Cast<AOliveCharacter>(TryGetPawnOwner());
	if (OliveCharacter) {
		Movement = OliveCharacter->GetCharacterMovement();
	}
}

void UOliveAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (Movement) {
		GroundSpeed = UKismetMathLibrary::VSizeXY(Movement->Velocity);
	}
}

