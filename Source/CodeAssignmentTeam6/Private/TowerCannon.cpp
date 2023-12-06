// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerCannon.h"
#include "Math/UnrealMathUtility.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "TowerBase.h"

// Sets default values
ATowerCannon::ATowerCannon():
	m_RotationSpeed(.4f),
	m_FireRate(.8f),
	m_FireRateTimer(m_FireRate),
	m_Damage(5),
	TurretCannonMesh(nullptr),
	ProjectileSpawn(nullptr),
	m_ProjectileToSpawn(nullptr),
	TurretCannonPivot(nullptr),
	TowerBase(nullptr)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretCannonPivot = CreateDefaultSubobject<USceneComponent>(TEXT("TowerCannonPivot"));
	TurretCannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerCannon"));
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));

	TurretCannonPivot->SetupAttachment(RootComponent);
	TurretCannonMesh->SetupAttachment(TurretCannonPivot);
	ProjectileSpawn->SetupAttachment(TurretCannonMesh);
}

// Called when the game starts or when spawned
void ATowerCannon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATowerCannon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_FireRateTimer += DeltaTime;
	m_FireRateTimer = FMath::Clamp(m_FireRateTimer, 0, m_FireRate);

	LookAtMouse();
}

void ATowerCannon::Fire()
{
	if (m_FireRateTimer >= m_FireRate)
	{
		m_FireRateTimer -= m_FireRate;
		if (IsValid(m_ProjectileToSpawn))
		{
			FTransform Spawn;
			Spawn.SetLocation(ProjectileSpawn->GetComponentLocation());

			float rand = FMath::RandRange(-0.03f, 0.03f);
			FQuat quatRot = ProjectileSpawn->GetComponentQuat();
			quatRot.Y += rand;
			quatRot.Z += rand;
			Spawn.SetRotation(quatRot);
			Spawn.SetScale3D(ProjectileSpawn->GetComponentScale() * 2);
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(m_ProjectileToSpawn, Spawn);

			if (IsValid(projectile))
				projectile->Init(m_Damage, 1500);
		}
	}
}

void ATowerCannon::Reset()
{
}

void ATowerCannon::LookAtMouse()
{
	FHitResult hit;
	UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHitResultUnderCursor(ECC_Visibility, false, hit);

	if (hit.bBlockingHit)
	{
		DrawDebugLine(GetWorld(), ProjectileSpawn->GetComponentLocation(), hit.ImpactPoint, FColor::Red);

		FRotator newRotation = (hit.ImpactPoint - TurretCannonPivot->GetComponentLocation()).Rotation();
		TurretCannonPivot->SetWorldRotation(FQuat::Slerp(GetActorRotation().Quaternion(), newRotation.Quaternion(), m_RotationSpeed));
	}
}

constexpr float ATowerCannon::GetRotationSpeed() const
{
	return m_RotationSpeed;
}

constexpr float ATowerCannon::GetFireRate() const
{
	return m_FireRate;
}

constexpr int ATowerCannon::GetDamage() const
{
	return m_Damage;
}

void ATowerCannon::HideInGame(bool hide)
{
	SetActorHiddenInGame(hide);
	SetActorTickEnabled(!hide);
}
