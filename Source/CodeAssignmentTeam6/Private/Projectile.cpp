// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBaseCharacter.h"

// Sets default values
AProjectile::AProjectile() :
	Projectile(nullptr),
	m_RandomAngle(0),
	m_ProjectileSpeed(1500),
	m_Damage(2)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile"));

	Projectile->SetSimulatePhysics(true);

	InitialLifeSpan = 5.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	Projectile->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnComponentBeginOverlap);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * m_ProjectileSpeed * DeltaTime);
}

void AProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (IsValid(OtherActor) && OtherActor != this)
	{
		AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(OtherActor);
		if (IsValid(enemy))
		{
			UGameplayStatics::ApplyDamage(enemy, m_Damage, nullptr, this, UDamageType::StaticClass());
		}
	}
	Destroy();
}

void AProjectile::Init(int Damage, float Speed)
{
	if (IsValid(this))
	{
		m_Damage = Damage;
		m_ProjectileSpeed = Speed;
		m_RandomAngle = FMath::RandRange(0.f, 0.5f);
	}
}

