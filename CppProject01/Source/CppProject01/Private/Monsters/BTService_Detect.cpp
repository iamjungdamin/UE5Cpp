// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/BTService_Detect.h"
#include "Monsters/ScarecrowAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Characters/BaseCharacter.h"
#include "Monsters/BaseMonster.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) {
		return;
	}

	ABaseMonster* ControllingCharacter = Cast<ABaseMonster>(ControllingPawn);
	if (nullptr == ControllingCharacter) {
		return;
	}
	ERangeType rangeType = ControllingCharacter->GetRangeType();

	UWorld* World = ControllingPawn->GetWorld();
	if (nullptr == World) {
		return;
	}

	FVector Origin = ControllingPawn->GetActorLocation();

	float radius = 0.f;
	if (rangeType == ERangeType::Narrow) {
		radius = 500.f;
	}
	else if (rangeType == ERangeType::Wide) {
		radius = 1000.f;
	}
	else {
		return;
	}

	// ControllingPawn?? ????x
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	TArray<FOverlapResult> OverlapResults;
	bool result = World->OverlapMultiByChannel(
		OverlapResults, Origin, FQuat::Identity,
		ECollisionChannel::ECC_EngineTraceChannel2,
		FCollisionShape::MakeSphere(radius),
		CollisionQueryParam
	);

	if (result) {
		for (auto& o : OverlapResults) {
			ABaseCharacter* Target = Cast<ABaseCharacter>(o.GetActor());
			if (Target && Target->GetController()->IsPlayerController()) {
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AScarecrowAIController::key_Target, Target);
				OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AScarecrowAIController::key_State, uint8(EState::CHASE));
				DrawDebugSphere(World, Origin, radius, 12, FColor::Green, false, 0.2f);

				return;
			}
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(AScarecrowAIController::key_Target, nullptr);
	OwnerComp.GetBlackboardComponent()->SetValueAsEnum(AScarecrowAIController::key_State, uint8(EState::PATROL));
	DrawDebugSphere(World, Origin, radius, 12, FColor::Red, false, 0.2f);
}
