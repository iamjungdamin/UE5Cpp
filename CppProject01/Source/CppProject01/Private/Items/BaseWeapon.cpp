// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/BaseWeapon.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
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
	IsEquipped = true;
	AttachActor(HandSocketName);
}

void ABaseWeapon::SetDamge(int value)
{
	Damage = value;
}

float ABaseWeapon::GetDamage() const
{
	return Damage;
}
