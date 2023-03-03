// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTService_UpdateBehavior.h"
#include "Monsters/ScarecrowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Monsters/BaseMonster.h"

UBTService_UpdateBehavior::UBTService_UpdateBehavior()
{
	NodeName = TEXT("UpdateBehavior");
	Interval = 1.0f;
}

void UBTService_UpdateBehavior::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (nullptr == Controller) {
		return;
	}

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) {
		return;
	}

	ABaseMonster* ControllingCharacter = Cast<ABaseMonster>(ControllingPawn);
	if (nullptr == ControllingCharacter) {
		return;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScarecrowAIController::key_Target);
	if (nullptr == Target) {
		ControllingCharacter->SetState(EState::PATROL);
		return;
	}

	ControllingCharacter->SetState(EState::CHASE);

}
