// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/OliveCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

}

