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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_AttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_ScoreAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_SpawnInterval;
	float m_SpawnTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy")
	TSubclassOf<class AEnemyBaseCharacter> m_EnemyToSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<class AWaveManager> m_WaveManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SpawnEnemy();
};
