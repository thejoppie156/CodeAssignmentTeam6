// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"
#include "Math/UnrealMathUtility.h"
#include "EnemyBaseCharacter.h"
#include "WaveManager.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AEnemySpawner::AEnemySpawner() :
	m_Health(5),
	m_MoveSpeed(150),
	m_Damage(2),
	m_AttackRange(150),
	m_ScoreAmount(1),
	m_SpawnInterval(3),
	m_SpawnTimer(0),
	m_EnemyToSpawn(nullptr),
	m_WaveManager(nullptr)

{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
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
	if (IsValid(enemy))
	{
		enemy->Init(m_Health, m_Damage, m_MoveSpeed, m_AttackRange, m_WaveManager);
		m_WaveManager->AddToEnemyArray(enemy);
	}
}

