// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BaseMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Math/UnrealMathUtility.h"

// Sets default values
ABaseMonster::ABaseMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

	maxHp = hp;
	
}

// Called every frame
void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABaseMonster::SetMontages(FString folderPath, int count)
{
	for (int i = 0; i < count; ++i) {
		FString Path = folderPath + FString::Printf(TEXT("/AM_Attack%02d"), i + 1);
		ConstructorHelpers::FObjectFinder<UAnimMontage>MontageAsset(*Path);

		if (MontageAsset.Succeeded()) {
			AttackMontages.Add(MontageAsset.Object);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
			continue;
		}
	}
}

void ABaseMonster::LoseHp(float amount)
{
	hp -= amount;

	if (hp <= 0) {
		//
	}
}

int ABaseMonster::GetHp()
{
	return hp;
}

void ABaseMonster::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	int randomIndex = FMath::RandRange(0, AttackMontages.Num());

	if (AnimInstance && AttackMontages[randomIndex]) {
		AnimInstance->Montage_Play(AttackMontages[randomIndex]);
	}
}

