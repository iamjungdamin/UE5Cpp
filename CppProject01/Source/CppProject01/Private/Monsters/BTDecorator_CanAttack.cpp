// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTDecorator_CanAttack.h"
#include "Monsters/ScarecrowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/BaseCharacter.h"
#include "Monsters/BaseMonster.h"

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
	
	ABaseMonster* ControllingCharacter = Cast<ABaseMonster>(ControllingPawn);
	if (nullptr == ControllingCharacter) {
		return false;
	}
	ERangeType rangeType = ControllingCharacter->GetRangeType();

	ABaseCharacter* Target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AScarecrowAIController::key_Target));
	if (nullptr == Target) {
		return false;
	}

	if (rangeType == ERangeType::Narrow) {
		float attackDist = 200.f;
		result = Target->GetDistanceTo(ControllingPawn) <= attackDist;
		return result;
	}
	else if (rangeType == ERangeType::Wide) {
		float attackDist = 1500.f;
		result = Target->GetDistanceTo(ControllingPawn) <= attackDist;
		return result;
	}

	return false;
}
