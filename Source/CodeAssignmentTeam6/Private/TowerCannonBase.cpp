// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerCannonBase.h"
#include "Math/UnrealMathUtility.h"
#include "TurretDataAsset.h"

// Sets default values for this component's properties
UTowerCannonBase::UTowerCannonBase() :
	m_RotationSpeed(1),
	m_FireRate(.7f),	
	m_Damage(2),
	TDataAsset(nullptr),
	m_FireRateTimer(m_FireRate)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTowerCannonBase::BeginPlay()
{
	Super::BeginPlay();

	// ...
	


}

// Called every frame
void UTowerCannonBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	m_FireRateTimer += DeltaTime;
	m_FireRateTimer = FMath::Clamp(m_FireRateTimer,0,m_FireRate);
	// ...
}

void UTowerCannonBase::Fire()
{
}

constexpr float UTowerCannonBase::GetRotationSpeed() const
{
	return m_RotationSpeed;
}

constexpr float UTowerCannonBase::GetFireRate() const
{
	return m_FireRate;
}

constexpr int UTowerCannonBase::GetDamage() const
{
	return m_Damage;
}

const TObjectPtr<class TurretDataAsset> UTowerCannonBase::GetTurretData() const
{
	return TObjectPtr<class TurretDataAsset>();
}

