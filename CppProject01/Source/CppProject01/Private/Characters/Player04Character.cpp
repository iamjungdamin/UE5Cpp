// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player04Character.h"
#include "UObject/ConstructorHelpers.h"

APlayer04Character::APlayer04Character()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Blueprints/Characters/Meshes/Player04/Cartoon_Man2_Final"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Characters/Meshes/Player04/Material__25"));
	if (MaterialAsset.Succeeded()) {
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstance(TEXT("/Game/Blueprints/Characters/ABP_Player04Anim"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	FString folderPath = "/Game/Blueprints/Characters/Animations/Player04";
	//SetMontages(folderPath);
}
