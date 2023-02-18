// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTTask_SetMovementSpeed.h"
#include "Monsters/ScarecrowAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTTask_SetMovementSpeed::UBTTask_SetMovementSpeed()
{
	NodeName = TEXT("SetMovementSpeed");
}

EBTNodeResult::Type UBTTask_SetMovementSpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) {
		return EBTNodeResult::Failed;
	}

	UCharacterMovementComponent* MovementComp = ControllingPawn->FindComponentByClass<UCharacterMovementComponent>();
	if (nullptr == MovementComp) {
		return EBTNodeResult::Failed;
	}

	if (speed == ESpeed::PATROL) {
		MovementComp->MaxWalkSpeed = 100.f;
		return EBTNodeResult::Succeeded;
	}
	else if (speed == ESpeed::RUN) {
		MovementComp->MaxWalkSpeed = 300.f;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

