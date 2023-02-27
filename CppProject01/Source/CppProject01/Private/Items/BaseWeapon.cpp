// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseWeapon.h"
#include "UObject/ConstructorHelpers.h"
#include "Items/CollisionComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCollisionComponent>(TEXT("CollisionComp"));
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::OnEquipped()
{
	isEquipped = true;
	AttachActor(HandSocketName);

	CollisionComp->SetCollisionMeshComp(ItemStaticMesh);
	CollisionComp->AddActorsToIgnore(GetOwner());
}

UCollisionComponent* ABaseWeapon::GetCollisionComp() const
{
	return CollisionComp;
}

void ABaseWeapon::SetDamge(int value)
{
	damage = value;
}

float ABaseWeapon::GetDamage() const
{
	return damage;
}
