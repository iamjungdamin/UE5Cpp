// Fill out your copyright notice in the Description page of Project Settings.


#include "Monsters/ScarecrowAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"


const FName AScarecrowAIController::key_HomePos(TEXT("HomePos"));
const FName AScarecrowAIController::key_PatrolPos(TEXT("PatrolPos"));
const FName AScarecrowAIController::key_Target(TEXT("Target"));

AScarecrowAIController::AScarecrowAIController()
{
	ConstructorHelpers::FObjectFinder<UBlackboardData>BBObject(TEXT("/Game/Blueprints/Monsters/BB_Scarecrow"));
	if (BBObject.Succeeded()) {
		BBAsset = BBObject.Object;
	}

	ConstructorHelpers::FObjectFinder<UBehaviorTree>BTObject(TEXT("/Game/Blueprints/Monsters/BT_Scarecrow"));
	if (BTObject.Succeeded()) {
		BTAsset = BTObject.Object;
	}
}

void AScarecrowAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = GetBlackboardComponent();

	if (UseBlackboard(BBAsset, BlackboardComp)) {
		BlackboardComp->SetValueAsVector(key_HomePos, InPawn->GetActorLocation());

		if (!RunBehaviorTree(BTAsset)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to Load BTAssets"));
		}
	}
}

