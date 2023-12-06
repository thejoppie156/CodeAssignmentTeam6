// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "TowerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WaveManager.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter():
	EnemyMesh(nullptr),
	m_Health(5),
	m_MoveSpeed(150),
	m_Range(150),
	m_Damage(2),
	m_AttackRate(1),
	m_AttackTimer(m_AttackRate)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	EnemyMesh->SetupAttachment(RootComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Tower = Cast<ATowerBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_AttackTimer += DeltaTime;
	m_AttackTimer = FMath::Clamp(m_AttackTimer, 0, m_AttackRate);

	if (IsValid(Tower) && GetDistanceTo(Tower) <= m_Range && m_AttackTimer >= m_AttackRate)
	{
		m_AttackTimer -= m_AttackRate;
		Attack();
	}
}

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyBaseCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	m_Health -= DamageAmount;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Hit for: %f amount of damage"), DamageAmount));
	if (m_Health <= 0)
	{
		m_WaveManager->RemoveFromEnemyArray(this);
		Destroy();
	}
	return DamageAmount;
}

void AEnemyBaseCharacter::Attack()
{
	UGameplayStatics::ApplyDamage(Tower, m_Damage, GetController(), this, UDamageType::StaticClass());
}

void AEnemyBaseCharacter::Init(int health, int damage, float moveSpeed, float attackRange, AWaveManager* waveManager)
{
	m_Health = health;
	m_Damage = damage;
	m_MoveSpeed = moveSpeed;
	m_WaveManager = waveManager;
}
