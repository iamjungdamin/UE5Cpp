// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OliveCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/BaseWeapon.h"
#include "Items/FireSword.h"
#include "Items/IceSword.h"
#include "Items/ElectricSword.h"

// Sets default values
AOliveCharacter::AOliveCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AOliveCharacter::BeginPlay()
{
	Super::BeginPlay(); 
	
	WeaponIndex = 0;
	SetWeapon(WeaponIndex);
}

void AOliveCharacter::MoveForward(float Value)
{
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

void AOliveCharacter::MoveRight(float Value)
{
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

void AOliveCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void AOliveCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

// Called every frame
void AOliveCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOliveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AOliveCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AOliveCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AOliveCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AOliveCharacter::LookUp);
	
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction(FName("ChangeWeapon"), IE_Pressed, this, &AOliveCharacter::ChangeWeapon);
	PlayerInputComponent->BindAction(FName("LeftClick"), IE_Pressed, this, &AOliveCharacter::BasicAttack);
	PlayerInputComponent->BindAction(FName("RightClick"), IE_Pressed, this, &AOliveCharacter::Charge);
	PlayerInputComponent->BindAction(FName("RightClick"), IE_Released, this, &AOliveCharacter::ChargedAttack);
	PlayerInputComponent->BindAction(FName("One"), IE_Pressed, this, &AOliveCharacter::Skill01);
	PlayerInputComponent->BindAction(FName("Two"), IE_Pressed, this, &AOliveCharacter::Skill02);
	PlayerInputComponent->BindAction(FName("Three"), IE_Pressed, this, &AOliveCharacter::Skill03);

}

void AOliveCharacter::SetWeapon(int value)
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

ABaseWeapon* AOliveCharacter::GetWeapon() const
{
	return Weapon;
}

void AOliveCharacter::ChangeWeapon()
{
	WeaponIndex = (WeaponIndex + 1) % 3;
	SetWeapon(WeaponIndex);

}

void AOliveCharacter::BasicAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("BasicAttack"));

}

void AOliveCharacter::Charge()
{
	UE_LOG(LogTemp, Warning, TEXT("Charge"));

}

void AOliveCharacter::ChargedAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("ChargedAttack"));

}

void AOliveCharacter::Skill01()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill01"));

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance) {
		//AnimInstance->Montage_Play();
	}

}

void AOliveCharacter::Skill02()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill02"));
}

void AOliveCharacter::Skill03()
{
	UE_LOG(LogTemp, Warning, TEXT("Skill03"));

}

