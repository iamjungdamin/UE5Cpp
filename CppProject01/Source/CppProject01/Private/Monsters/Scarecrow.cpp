// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/Scarecrow.h"
#include "UObject/ConstructorHelpers.h"

AScarecrow::AScarecrow()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Ch14_nonPBR"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Monsters/Meshes/Ch14_nonPBR/Body"));
	if (MaterialAsset.Succeeded()) {
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}
}

