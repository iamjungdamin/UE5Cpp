// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/CollisionAns.h"
#include "Characters/BaseCharacter.h"
#include "Items/BaseWeapon.h"
#include "Items/CollisionComponent.h"

void UCollisionAns::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character) {
		return;
	}

	ABaseWeapon* Weapon = Character->GetWeapon();
	if (!Weapon) {
		return;
	}
	
	UCollisionComponent* CollisionComp = Weapon->GetCollisionComp();
	if (CollisionComp) {
		CollisionComp->EnableCollision();
	}

}

void UCollisionAns::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABaseCharacter* Character = Cast<ABaseCharacter>(MeshComp->GetOwner());
	if (!Character) {
		return;
	}

	ABaseWeapon* Weapon = Character->GetWeapon();
	if (!Weapon) {
		return;
	}

	UCollisionComponent* CollisionComp = Weapon->GetCollisionComp();
	if (CollisionComp) {
		CollisionComp->DisableCollision();
	}

}
