// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/BaseEquipable.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ABaseEquipable::ABaseEquipable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Capsule);

	ItemSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemSkeletalMesh"));
	ItemSkeletalMesh->SetupAttachment(GetRootComponent());

	ItemStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemStaticMesh"));
	ItemStaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABaseEquipable::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseEquipable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseEquipable::OnEquipped()
{
	IsEquipped = true;
}

void ABaseEquipable::OnUnequipped()
{
	if (IsEquipped) {
		IsEquipped = false;
	}
}

void ABaseEquipable::SetIsEquipped(bool value)
{
	IsEquipped = value;
}

bool ABaseEquipable::GetIsEquipped() const
{
	return IsEquipped;
}

void ABaseEquipable::AttachActor(FName socketName)
{
	ACharacter* owner = GetOwner<ACharacter>();
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(owner->GetMesh(), TransformRules, socketName);
}

