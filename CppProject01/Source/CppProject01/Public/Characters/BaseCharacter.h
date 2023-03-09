// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ABaseWeapon;

UCLASS()
class CPPPROJECT01_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

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
	float hp = 1000.f;
	float maxHp;

	ABaseWeapon* Weapon;
	int WeaponIndex;

	int comboCount = 0;
	bool comboUpdate = false;

protected:
	void SetMontages(FString folderPath);

	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* DashMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* BasicAttackMontages[3];

	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* ChargedAttackMontages[3];

	UPROPERTY(EditDefaultsOnly, Category = Montages)
		UAnimMontage* SkillMontages[3];

private:
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
	void SetWeapon(int value);
	ABaseWeapon* GetWeapon() const;

	void SetIsIdle(bool value);

	void SaveCombo();
	void ResetCombo();
};

