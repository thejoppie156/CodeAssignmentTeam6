// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"


UCLASS()
class CODEASSIGNMENTTEAM6_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int m_Health;
	float m_MoveSpeed;
	int m_Damage;
	float m_AttackRange;


	float m_SpawnInterval;
	float m_SpawnTimer;

	UPROPERTY()
	TSubclassOf<class AEnemyBaseCharacter> m_EnemyToSpawn;
	UPROPERTY()
	TObjectPtr<class AWaveManager> m_WaveManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnEnemy();
};
