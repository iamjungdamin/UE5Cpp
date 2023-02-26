// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"
#include "UObject/ConstructorHelpers.h"

#include "Items/BaseWeapon.h"
#include "Items/FireSword.h"
#include "Items/IceSword.h"
#include "Items/ElectricSword.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 60.f), FRotator(0.f, -10.f, 0.f));

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	maxHp = hp;

	WeaponIndex = 0;
	SetWeapon(WeaponIndex);
}

void ABaseCharacter::MoveForward(float Value)
{
	if (!isIdle) {
		return;
	}

	if (Controller && (Value != 0.f)) {
		//FVector Forward = GetActorForwardVector();
		//AddMovementInput(Forward, Value);

		// find out which way is forward
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation{ 0.f, ControlRotation.Yaw, 0.f };

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::MoveRight(float Value)
{
	if (!isIdle) {
		return;
	}

	if (Controller && (Value != 0.f)) {
		//FVector Right = GetActorRightVector();
		//AddMovementInput(Right, Value);

		// find out which way is right
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation{ 0.f, ControlRotation.Yaw, 0.f };

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ABaseCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ABaseCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ABaseCharacter::LookUp);

	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(FName("ChangeWeapon"), IE_Pressed, this, &ABaseCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction(FName("Dash"), IE_Pressed, this, &ABaseCharacter::Dash);

	PlayerInputComponent->BindAction(FName("LeftClick"), IE_Pressed, this, &ABaseCharacter::ComboAttack);
	PlayerInputComponent->BindAction(FName("RightClick"), IE_Pressed, this, &ABaseCharacter::Charge);
	PlayerInputComponent->BindAction(FName("RightClick"), IE_Released, this, &ABaseCharacter::ChargedAttack);
	PlayerInputComponent->BindAction(FName("One"), IE_Pressed, this, &ABaseCharacter::Skill01);
	PlayerInputComponent->BindAction(FName("Two"), IE_Pressed, this, &ABaseCharacter::Skill02);
	PlayerInputComponent->BindAction(FName("Three"), IE_Pressed, this, &ABaseCharacter::Skill03);

}

void ABaseCharacter::SetMontages(FString folderPath)
{
	TArray<FString> FileNames = {
		"/AM_Dash",

		"/AM_FireBasicAttack",
		"/AM_IceBasicAttack",
		"/AM_ElectricBasicAttack",

		"/AM_FireChargedAttack",
		"/AM_IceChargedAttack",
		"/AM_ElectricChargedAttack",

		"/AM_FireSkill",
		"/AM_IceSkill",
		"/AM_ElectricSkill"
	};

	for (int i = 0; i < FileNames.Num(); ++i) {
		FString Path = folderPath + FileNames[i];
		ConstructorHelpers::FObjectFinder<UAnimMontage>MontageAsset(*Path);
		
		if (MontageAsset.Succeeded()) {
			if (i == 0) {
				DashMontage = MontageAsset.Object;
			}
			else if (i < 4) {
				BasicAttackMontage[i - 1] = MontageAsset.Object;
			}
			else if (i < 7) {
				ChargedAttackMontage[i - 4] = MontageAsset.Object;
			}
			else if (i < 10) {
				SkillMontage[i - 7] = MontageAsset.Object;
			}
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Failed to Load Assets"));
			continue;
		}
	}
}

void ABaseCharacter::SetWeapon(int value)
{
	if (Weapon) {
		Weapon->OnUnequipped();
		Weapon->Destroy();
	}

	if (WeaponIndex == 0) {
		Weapon = GetWorld()->SpawnActor<AFireSword>(GetActorLocation(), GetActorRotation());
		Weapon->SetOwner(Cast<AActor>(this));
		Weapon->SetInstigator(Cast<APawn>(this));

		Weapon->OnEquipped();
	}
	else if (WeaponIndex == 1) {
		Weapon = GetWorld()->SpawnActor<AIceSword>(GetActorLocation(), GetActorRotation());
		Weapon->SetOwner(Cast<AActor>(this));
		Weapon->SetInstigator(Cast<APawn>(this));

		Weapon->OnEquipped();
	}
	else if (WeaponIndex == 2) {
		Weapon = GetWorld()->SpawnActor<AElectricSword>(GetActorLocation(), GetActorRotation());
		Weapon->SetOwner(Cast<AActor>(this));
		Weapon->SetInstigator(Cast<APawn>(this));

		Weapon->OnEquipped();
	}
}

ABaseWeapon* ABaseCharacter::GetWeapon() const
{
	return Weapon;
}

void ABaseCharacter::ChangeWeapon()
{
	if (!isIdle) {
		return;
	}

	WeaponIndex = (WeaponIndex + 1) % 3;
	SetWeapon(WeaponIndex);

	UE_LOG(LogTemp, Log, TEXT("WeaponIndex = %d"), WeaponIndex);
}

void ABaseCharacter::Dash()
{
	if (!isIdle) {
		return;
	}

	FVector Forward = GetActorForwardVector() * 20000.f;
	FVector Down = FVector(0, 0, -300.f);
	LaunchCharacter(Forward + Down, true, true);

	//UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	//if (AnimInstance && DashMontage) {
	//	AnimInstance->Montage_Play(DashMontage);
	//}

}

void ABaseCharacter::ComboAttack()
{
	if (!isIdle) {
		comboUpdate = true;
		return;
	}

	BasicAttack();
}

void ABaseCharacter::BasicAttack()
{
	UE_LOG(LogTemp, Log, TEXT("BasicAttack"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && BasicAttackMontage[WeaponIndex]) {
		isIdle = false;

		AnimInstance->Montage_Play(BasicAttackMontage[WeaponIndex]);
		FName SectionName = FName();
		if (comboCount == 0) {
			SectionName = FName("01");
		}
		else if (comboCount == 1) {
			SectionName = FName("02");
		}
		else if (comboCount == 2) {
			SectionName = FName("03");
		}
		else if (comboCount == 3) {
			SectionName = FName("04");
		}
		else if (comboCount == 4) {
			SectionName = FName("05");
		}
		AnimInstance->Montage_JumpToSection(SectionName, BasicAttackMontage[WeaponIndex]);
	}

}

void ABaseCharacter::Charge()
{
	if (!isIdle) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Charge"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ChargedAttackMontage[WeaponIndex]) {
		isIdle = false;

		AnimInstance->Montage_Play(ChargedAttackMontage[WeaponIndex]);
		AnimInstance->Montage_JumpToSection(FName("01"), ChargedAttackMontage[WeaponIndex]);
	}

}

void ABaseCharacter::ChargedAttack()
{
	UE_LOG(LogTemp, Log, TEXT("ChargedAttack"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ChargedAttackMontage[WeaponIndex]) {

		AnimInstance->Montage_Play(ChargedAttackMontage[WeaponIndex]);
		AnimInstance->Montage_JumpToSection(FName("02"), ChargedAttackMontage[WeaponIndex]);
	}

}

void ABaseCharacter::Skill01()
{
	if (!isIdle) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Skill01"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && SkillMontage[WeaponIndex]) {
		isIdle = false;

		AnimInstance->Montage_Play(SkillMontage[WeaponIndex]);
		AnimInstance->Montage_JumpToSection(FName("01"), SkillMontage[WeaponIndex]);
	}

}

void ABaseCharacter::Skill02()
{
	if (!isIdle) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Skill02"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && SkillMontage[WeaponIndex]) {
		isIdle = false;

		AnimInstance->Montage_Play(SkillMontage[WeaponIndex]);
		AnimInstance->Montage_JumpToSection(FName("02"), SkillMontage[WeaponIndex]);
	}
}

void ABaseCharacter::Skill03()
{
	if (!isIdle) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Skill03"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && SkillMontage[WeaponIndex]) {
		isIdle = false;

		AnimInstance->Montage_Play(SkillMontage[WeaponIndex]);
		AnimInstance->Montage_JumpToSection(FName("03"), SkillMontage[WeaponIndex]);
	}
}

void ABaseCharacter::SetIsIdle(bool value)
{
	isIdle = value;
}

void ABaseCharacter::SaveCombo()
{
	int maxComboCount = 0;
	if (WeaponIndex == 0) {
		maxComboCount = 2;
	}
	else if (WeaponIndex == 1) {
		maxComboCount = 3;
	}
	else if (WeaponIndex == 2) {
		maxComboCount = 4;
	}

	if (comboUpdate) {
		comboUpdate = false;
		comboCount += 1;

		if (comboCount > maxComboCount) {
			return;
		}

		if (comboCount > 0) {
			BasicAttack();
		}
	}

}

void ABaseCharacter::ResetCombo()
{
	comboCount = 0;
}
