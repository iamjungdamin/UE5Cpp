// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/FireSword.h"
#include "UObject/ConstructorHelpers.h"

AFireSword::AFireSword()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/Blueprints/Items/Meshes/SM_Sword"));
	if (MeshAsset.Succeeded()) {
		ItemStaticMesh->SetStaticMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Items/Materials/M_WeaponSet_1"));
	if (MaterialAsset.Succeeded()) {
		ItemStaticMesh->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}
}

