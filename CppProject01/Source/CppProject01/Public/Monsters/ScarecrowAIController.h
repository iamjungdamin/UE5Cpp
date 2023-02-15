// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ScarecrowAIController.generated.h"

class UBlackboardData;
class UBehaviorTree;

/**
 * 
 */
UCLASS()
class CPPPROJECT01_API AScarecrowAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AScarecrowAIController();
	virtual void OnPossess(APawn* InPawn) override;

public:
	FName key_HomePos;
	FName key_PatrolPos;

private:
	UPROPERTY()
		UBlackboardData* BBAsset;

	UPROPERTY()
		UBehaviorTree* BTAsset;
};
