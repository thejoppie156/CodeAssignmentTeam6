// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

UCLASS()
class CODEASSIGNMENTTEAM6_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<class AEnemyBaseCharacter*> m_EnemiesAlive;
	UPROPERTY()
	TArray<class AEnemySpawner*> m_Spawners;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddToEnemyArray(class AEnemyBaseCharacter* const enemy);
	void AddToSpawnerArray(class AEnemySpawner* const spawner);

	void RemoveFromEnemyArray(class AEnemyBaseCharacter* enemy);
	void RemoveFromSpawnerArray(class AEnemySpawner* spawner);

	const TArray<class AEnemyBaseCharacter*> GetEnemyArray() const;
};
