// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTDecorator_CanAttack.h"
#include "Monsters/ScarecrowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/BaseCharacter.h"

UBTDecorator_CanAttack::UBTDecorator_CanAttack()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_CanAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) {
		return false;
	}

	ABaseCharacter* Target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScarecrowAIController::key_Target));
	if (nullptr == Target) {
		return false;
	}

	float attackDist = 200.f;
	result = Target->GetDistanceTo(ControllingPawn) <= attackDist;
	return result;
}
