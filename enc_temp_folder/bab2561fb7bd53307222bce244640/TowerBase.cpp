// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBase.h"
#include "TowerCannonBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATowerBase::ATowerBase() :
	m_MaxHealth(100),
	m_Health(m_MaxHealth),	
	TurretPosition(nullptr),
	TurretBase(nullptr),
	TurretCannon(nullptr),
	m_PlayerController(nullptr)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TurretPosition = CreateDefaultSubobject<USceneComponent>("TowerCannonPosition");
	TurretCannon = CreateDefaultSubobject<UTowerCannonBase>("TowerCannon");
	TurretBase = CreateDefaultSubobject<UStaticMeshComponent>("TowerBase");
}

// Called when the game starts or when spawned
void ATowerBase::BeginPlay() 
{
	Super::BeginPlay();
	
	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void ATowerBase::LookAtMouse()
{
	FHitResult hit;
	//playerController->DeprojectMousePositionToWorld(TargetLocation, );
	m_PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,hit);

	DrawDebugLine(GetWorld(), TurretPosition->GetComponentLocation(), hit.ImpactPoint, FColor::Red);

}

void ATowerBase::Attack()
{
}

// Called every frame
void ATowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TurretPosition && TurretCannon)
		LookAtMouse();
}

// Called to bind functionality to input
void ATowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

