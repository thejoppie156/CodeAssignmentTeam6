// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Math/UnrealMathUtility.h"
#include "EnemyBaseCharacter.h"
#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	m_WaveManager = Cast<AWaveManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWaveManager::StaticClass()));
	if (IsValid(m_WaveManager))
	{
		m_WaveManager->AddToSpawnerArray(this);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_SpawnTimer += DeltaTime;
	FMath::Clamp(m_SpawnTimer, 0, m_SpawnInterval);

	if (IsValid(m_WaveManager) && m_SpawnTimer >= m_SpawnInterval)
	{
		m_SpawnTimer -= m_SpawnInterval;
		SpawnEnemy();
	}
}

void AEnemySpawner::SpawnEnemy()
{
	AEnemyBaseCharacter* enemy = GetWorld()->SpawnActor<AEnemyBaseCharacter>(m_EnemyToSpawn, GetActorTransform());
	enemy->Init(m_Health, m_Damage, m_MoveSpeed, m_AttackRange);

	m_WaveManager->AddToEnemyArray(enemy);

	//add enemy to wavemanager list to keep track how many are alive
}

