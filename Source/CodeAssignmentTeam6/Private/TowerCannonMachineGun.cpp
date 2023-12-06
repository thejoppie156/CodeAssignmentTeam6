// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerCannonMachineGun.h"
#include "Projectile.h"

ATowerCannonMachineGun::ATowerCannonMachineGun()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerCannonMachineGun::BeginPlay()
{
	Super::BeginPlay();
}

void ATowerCannonMachineGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerCannonMachineGun::Fire()
{
	if (m_WindUpTimer >= m_WindUpTime)
	{
		if (m_FireRateTimer >= m_FireRate)
		{
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot via Towerbase!"));
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
}
