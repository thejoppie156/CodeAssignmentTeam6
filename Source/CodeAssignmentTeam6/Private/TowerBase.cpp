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

// Sets default values
ATowerBase::ATowerBase() :
	m_MaxHealth(100),
	m_Health(m_MaxHealth),
	TurretBase(nullptr),
	TowerCannonComponent(nullptr),
	TurretCannon(nullptr),
	TurretCannonAttachPoint(nullptr),
	m_PlayerController(nullptr),
	ProjectileSpawn(nullptr),
	m_ProjectileToSpawn(nullptr),
	CameraBoom(nullptr),
	Camera(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TurretCannonAttachPoint = CreateDefaultSubobject<USceneComponent>(TEXT("TowerCannonPivot"));
	TurretCannon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerCannon"));
	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawn"));

	TowerCannonComponent = CreateDefaultSubobject<UTowerCannonBase>(TEXT("TowerCannonActorComponent"));

	TurretBase->SetupAttachment(GetRootComponent());
	TurretCannonAttachPoint->SetupAttachment(TurretBase);
	TurretCannon->SetupAttachment(TurretCannonAttachPoint);
	ProjectileSpawn->SetupAttachment(TurretCannon);

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
		FInputModeGameOnly mode;
		m_PlayerController->SetInputMode(mode);
		m_PlayerHUD->AddToViewport();
	}	
}

void ATowerBase::LookAtMouse()
{
	
	FHitResult hit;
	m_PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, hit);

	
	if (hit.bBlockingHit)
	{		
		DrawDebugLine(GetWorld(), ProjectileSpawn->GetComponentLocation(), hit.ImpactPoint, FColor::Red);

		FRotator newRotation = (hit.ImpactPoint - TurretCannonAttachPoint->GetComponentLocation()).Rotation();
		TurretCannonAttachPoint->SetWorldRotation(newRotation);
	}
}

void ATowerBase::OnShoot()
{
	if (IsValid(TowerCannonComponent) && TowerCannonComponent->m_FireRateTimer >= TowerCannonComponent->GetFireRate())
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
		
	}
	
	/*if (ACTurretCannon)
		ACTurretCannon->Fire();*/
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LookAtMouse();		
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
	if (m_Health <= 0)
	{
		Destroy();
	}
	return DamageAmount;
}
