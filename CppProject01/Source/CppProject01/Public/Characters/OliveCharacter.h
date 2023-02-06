// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "OliveCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABaseWeapon;

UCLASS()
class CPPPROJECT01_API AOliveCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOliveCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* ViewCamera;

	bool isIdle = true;

	ABaseWeapon* Weapon;
	int WeaponIndex;

	int comboCount = 0;
	bool comboUpdate = false;

private:	
	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* DashMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* BasicAttackMontage[3];

	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* ChargedAttackMontage[3];

	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* SkillMontage[3];

private:
	void SetWeapon(int value);
	ABaseWeapon* GetWeapon() const;

	void ChangeWeapon();
	void Dash();

	void ComboAttack();
	void BasicAttack();
	void Charge();
	void ChargedAttack();
	void Skill01();
	void Skill02();
	void Skill03();

public:
	void SetIsIdle(bool value);

	void SaveCombo();
	void ResetCombo();
};

