// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player01Character.h"
#include "UObject/ConstructorHelpers.h"

APlayer01Character::APlayer01Character()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("/Game/Blueprints/Characters/Meshes/Player01/8__Paranoid_Girl"));
	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}

	ConstructorHelpers::FObjectFinder<UMaterial>MaterialAsset(TEXT("/Game/Blueprints/Characters/Meshes/Player01/Material__25"));
	if (MaterialAsset.Succeeded()) {
		GetMesh()->SetMaterial(0, MaterialAsset.Object);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
	}
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}
