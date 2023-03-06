// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Golem.h"
#include "UObject/ConstructorHelpers.h"

AGolem::AGolem()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Golem/Mutant"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Golem/mutant_M"));
	if (MaterialAsset.Succeeded()) {
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstance(TEXT("/Game/Blueprints/Monsters/ABP_GolemAnim"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
}
