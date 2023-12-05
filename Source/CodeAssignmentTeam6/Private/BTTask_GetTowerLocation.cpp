// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetTowerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TowerBase.h"
#include "NavigationSystem.h"

UBTTask_GetTowerLocation::UBTTask_GetTowerLocation()
{
	NodeName = TEXT("Get Tower Location");

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_GetTowerLocation, BlackboardKey));
}

EBTNodeResult::Type UBTTask_GetTowerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const APawn* tower = UGameplayStatics::GetPlayerPawn(GetWorld(),0);
	if (IsValid(tower))
	{		
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), tower->GetActorLocation());
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

FString UBTTask_GetTowerLocation::GetStaticDescription() const
{
	return FString::Printf(TEXT("Vector: %s"), *GetSelectedBlackboardKey().ToString());
}
