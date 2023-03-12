// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Golem.h"
#include "UObject/ConstructorHelpers.h"
#include "Monsters/ScarecrowAIController.h"

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

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	SetActorScale3D(FVector(5.f, 5.f, 5.f));

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FClassFinder<UAnimInstance>AnimInstance(TEXT("/Game/Blueprints/Monsters/ABP_GolemAnim"));
	if (AnimInstance.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimInstance.Class);
	}

	FString folderPath = "/Game/Blueprints/Monsters/Animations/Golem";
	SetMontages(folderPath, 2);

	AIControllerClass = AScarecrowAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
