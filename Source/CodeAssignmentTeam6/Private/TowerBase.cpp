// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "TowerCannonBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"
#include "PlayerHUD.h"
#include "GameOverHUD.h"
#include "TowerCannon.h"

// Sets default values
ATowerBase::ATowerBase() :
	m_MaxHealth(100),
	m_Health(m_MaxHealth),
	TurretBase(nullptr),
	TowerCannonComponent(nullptr),
	//TurretCannon(nullptr),
	TurretCannonAttachPoint(nullptr),
	m_PlayerController(nullptr),
	//ProjectileSpawn(nullptr),
	//m_ProjectileToSpawn(nullptr),
	CameraBoom(nullptr),
	Camera(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TurretCannonAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TowerCannonPivot"));
	//m_TurretCannon = CreateDefaultSubobject<UChildActorComponent>(TEXT("TowerCannon"));
	//ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));

	TowerCannonComponent = CreateDefaultSubobject<UTowerCannonBase>(TEXT("TowerCannonActorComponent"));

	TurretBase->SetupAttachment(GetRootComponent());
	TurretCannonAttachPoint->SetupAttachment(TurretBase);
	//m_TurretCannon->SetupAttachment(TurretCannonAttachPoint);
	//ProjectileSpawn->SetupAttachment(TurretCannon);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(TurretBase);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom);
	Camera->bUsePawnControlRotation = false;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay() 
{
	Super::BeginPlay();

	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	m_PlayerHUD = Cast<UPlayerHUD>(CreateWidget(GetWorld(), m_PlayerHUDClass));
	if (IsValid(m_PlayerHUD))
	{		
		//FInputModeGameOnly mode;
		//m_PlayerController->SetInputMode(mode);
		m_PlayerHUD->AddToViewport();

		m_PlayerHUD->SetHealth(m_Health, 100);
	}
	for (TSubclassOf<ATowerCannon>& turretCannonclass : m_TowerCannonsToSpawn)
	{
		ATowerCannon* tower = GetWorld()->SpawnActor<ATowerCannon>(turretCannonclass, TurretCannonAttachPoint->GetComponentTransform());
		tower->AttachToComponent(TurretCannonAttachPoint, FAttachmentTransformRules::KeepWorldTransform);
		Towers.Add(tower);
		tower->HideInGame(true);
	}
	
	if (Towers.Num()!=0)
	{
		m_TurretCannon = Towers[0];
		m_TurretCannon->HideInGame(false);
	}
	//m_TurretCannon = GetWorld()->SpawnActor<ATowerCannon>(ATowerCannon::StaticClass(), TurretCannonAttachPoint->GetComponentTransform());
	//m_TurretCannon; GetDefaultTurret cannon and store it as variable
	//Attach m_TurretCannon to Attachpoint on towerbase
	//Initialize other turret cannons and store them in Towers (so all of them are in a single array as base TurretCannon class) 
	//Use Q and E to swap to next/previous Turret
	//call Fire onShoot on the current m_TurretCannon for shooting
	// 
	//Towers.Add();

}

void ATowerBase::OnSwapTurret(float val)
{
	int index;
	if (Towers.IsValidIndex(m_TowersIndex + val))
	{
		index = m_TowersIndex + val;
	}
	else
	{
		if (val > 0)
		{
			index = 0;
		}
		else
		{
			index = Towers.Num() - 1;
		}
	}

	if (m_TowersIndex == index)
		return;

	m_TowersIndex = index;	
	m_TurretCannon->HideInGame(true);
	m_TurretCannon = Towers[m_TowersIndex];
	m_TurretCannon->HideInGame(false);
}

void ATowerBase::OnShoot()
{
	/*if (IsValid(TowerCannonComponent) && TowerCannonComponent->m_FireRateTimer >= TowerCannonComponent->GetFireRate())
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Shoot via Towerbase!"));
		TowerCannonComponent->m_FireRateTimer -= TowerCannonComponent->GetFireRate();
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
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(m_ProjectileToSpawn,Spawn);

			if(IsValid(projectile))
				projectile->Init(TowerCannonComponent->GetDamage(), 1500);
		}
		
	}*/
	
	/*if (ACTurretCannon)
		ACTurretCannon->Fire();*/

	//Call Fire on ATowerCannon
	//TowerCannon is being inherited for each different tower (3)

	
	m_TurretCannon->Fire();
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ATowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATowerBase::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	m_Health -= DamageAmount;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Tower Hit for: %f amount of damage"), DamageAmount));

	if(IsValid(m_PlayerHUD))
		m_PlayerHUD->SetHealth(m_Health, 100);

	if (m_Health <= 0)
	{
		m_GameOverHUD = Cast<UGameOverHUD>(CreateWidget(GetWorld(), m_GameOverHUDClass));
		if (IsValid(m_GameOverHUD))
		{
			m_PlayerController->Pause();
			m_GameOverHUD->AddToViewport();
		}
	}
	return DamageAmount;
}

const TObjectPtr<UPlayerHUD> ATowerBase::GetPlayerHUD() const
{
	return m_PlayerHUD;
}
