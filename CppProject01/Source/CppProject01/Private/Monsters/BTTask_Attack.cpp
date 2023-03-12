// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTTask_Attack.h"
#include "Monsters/ScarecrowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Monsters/BaseMonster.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ControllingCharacter = Cast<ABaseMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingCharacter) {
		return EBTNodeResult::Failed;
	}

	ControllingCharacter->SetIsIdle(false);
	ControllingCharacter->Attack();

	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (ControllingCharacter->GetIsIdle()) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
