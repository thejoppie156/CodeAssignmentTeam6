// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "Kismet/GameplayStatics.h"
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
	TurretCannonAttachPoint(nullptr),
	m_TurretCannon(nullptr),
	m_PlayerController(nullptr),
	CameraBoom(nullptr),
	Camera(nullptr),
	m_PlayerHUD(nullptr),
	m_PlayerHUDClass(nullptr),
	m_GameOverHUDClass(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TurretCannonAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TowerCannonPivot"));

	TurretBase->SetupAttachment(GetRootComponent());
	TurretCannonAttachPoint->SetupAttachment(TurretBase);

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
		m_PlayerHUD->AddToViewport();

		m_PlayerHUD->SetHealth(m_Health, 100);
	}
	for (TSubclassOf<ATowerCannon>& turretCannonclass : m_TowerCannonsToSpawn)
	{
		ATowerCannon* tower = GetWorld()->SpawnActor<ATowerCannon>(turretCannonclass, TurretCannonAttachPoint->GetComponentTransform());
		tower->AttachToComponent(TurretCannonAttachPoint, FAttachmentTransformRules::KeepWorldTransform);
		Towers.Add(tower);
		tower->HideInGame(true);
		tower->SetActorEnableCollision(false);
	}
	
	if (Towers.Num()!=0)
	{
		m_TurretCannon = Towers[0];
		m_TurretCannon->HideInGame(false);
	}
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

	FRotator temp = Towers[m_TowersIndex]->GetActorRotation();
	m_TowersIndex = index;

	m_TurretCannon->HideInGame(true);
	m_TurretCannon->Reset();
	m_TurretCannon = Towers[m_TowersIndex];

	m_TurretCannon->HideInGame(false);
	m_TurretCannon->SetActorRotation(temp);
}

void ATowerBase::OnShoot()
{
	if (IsValid(m_TurretCannon))
		m_TurretCannon->Fire();
}

void ATowerBase::OnShootReleased()
{
	if (IsValid(m_TurretCannon))
		m_TurretCannon->Reset();
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
		UGameOverHUD * gameOverHUD = Cast<UGameOverHUD>(CreateWidget(GetWorld(), m_GameOverHUDClass));
		if (IsValid(gameOverHUD))
		{
			m_PlayerController->Pause();
			gameOverHUD->AddToViewport();
		}
	}
	return DamageAmount;
}

const TObjectPtr<UPlayerHUD> ATowerBase::GetPlayerHUD() const
{
	return m_PlayerHUD;
}
