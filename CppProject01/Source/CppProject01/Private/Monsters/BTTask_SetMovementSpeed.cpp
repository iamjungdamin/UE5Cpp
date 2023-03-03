// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTTask_SetMovementSpeed.h"
#include "Monsters/ScarecrowAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Monsters/BaseMonster.h"

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

	ABaseMonster* ControllingCharacter = Cast<ABaseMonster>(ControllingPawn);
	if (ControllingCharacter->GetState() == EState::PATROL) {
		MovementComp->MaxWalkSpeed = 100.f;
		return EBTNodeResult::Succeeded;
	}
	else if (ControllingCharacter->GetState() == EState::CHASE) {
		MovementComp->MaxWalkSpeed = 300.f;
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

