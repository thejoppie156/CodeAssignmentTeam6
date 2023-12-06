// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController():
	BehaviorTree(nullptr),
	BehaviorTreeComponent(nullptr),
	BlackboardComponent(nullptr)
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

TObjectPtr<class UBehaviorTree> AEnemyAIController::GetBehaviorTree() const
{
	return BehaviorTree;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(BehaviorTreeComponent) && IsValid(BlackboardComponent))
	{	
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}
