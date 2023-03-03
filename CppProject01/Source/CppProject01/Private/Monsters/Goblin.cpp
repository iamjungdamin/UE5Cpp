// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Goblin.h"
#include "UObject/ConstructorHelpers.h"
#include "Monsters/ScarecrowAIController.h"

AGoblin::AGoblin()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Goblin/Ch34_nonPBR"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Goblin/phong1"));
	if (MaterialAsset.Succeeded()) {
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));

	AIControllerClass = AScarecrowAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
