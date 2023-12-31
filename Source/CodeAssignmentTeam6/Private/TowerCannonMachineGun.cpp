// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerCannonMachineGun.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

ATowerCannonMachineGun::ATowerCannonMachineGun() :
	m_IncreaseFireRate(.02f),
	m_MaxFireRate(.1f),
	m_BaseFireRate(m_FireRate),
	m_WindUpTimer(.7f),
	m_WindUpTime(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_FireRate = 0.3f;
	m_BaseFireRate = m_FireRate;
	m_RotationSpeed = 0.1f;
	m_Damage = 2;
}

void ATowerCannonMachineGun::BeginPlay()
{
	Super::BeginPlay();

	m_FireRate = 0.3f;
}

void ATowerCannonMachineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerCannonMachineGun::Fire()
{	
	m_WindUpTime += UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	m_WindUpTime = FMath::Clamp(m_WindUpTime,0, m_WindUpTimer);
	if (m_WindUpTime >= m_WindUpTimer)
	{
		if (m_FireRateTimer >= m_FireRate)
		{
			m_FireRateTimer -= m_FireRate;
			m_FireRate -= m_IncreaseFireRate;
			m_FireRate = FMath::Clamp(m_FireRate, m_MaxFireRate, m_BaseFireRate);
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::Printf(TEXT("fire rate: %f!"),m_FireRate));
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
					projectile->Init(m_Damage, 1700);
			}
		}
	}
}

void ATowerCannonMachineGun::Reset()
{
	m_WindUpTime = 0;
	m_FireRate = m_BaseFireRate;
}
