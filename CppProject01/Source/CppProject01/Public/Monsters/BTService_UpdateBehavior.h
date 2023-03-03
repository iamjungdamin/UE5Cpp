// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_UpdateBehavior.generated.h"

/**
 * 
 */
UCLASS()
class CPPPROJECT01_API UBTService_UpdateBehavior : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_UpdateBehavior();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
