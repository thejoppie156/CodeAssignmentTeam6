// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPlayerController.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "TowerBase.h"
#include "Engine/LocalPlayer.h"
#include "InputConfigData.h"
#include "InputActionValue.h"

ATowerPlayerController::ATowerPlayerController():
	InputActions(nullptr),
	InputMapping(nullptr),
	m_ControlledTower(nullptr)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATowerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		Subsystem->AddMappingContext(InputMapping, 0);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputActions->Shoot, ETriggerEvent::Triggered, this, &ATowerPlayerController::OnShoot);
		EnhancedInputComponent->BindAction(InputActions->Shoot, ETriggerEvent::Completed, this, &ATowerPlayerController::OnShootReleased);

		EnhancedInputComponent->BindAction(InputActions->SwapTurretCannon, ETriggerEvent::Started, this, &ATowerPlayerController::OnSwapTurretCannon);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Input Created!"));
	}
}

void ATowerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	m_ControlledTower = Cast<ATowerBase>(GetPawn());
}

void ATowerPlayerController::OnShoot()
{
	if (IsValid(m_ControlledTower))
		m_ControlledTower->OnShoot();	
}

void ATowerPlayerController::OnShootReleased()
{
	if (IsValid(m_ControlledTower))
		m_ControlledTower->OnShootReleased();
}

void ATowerPlayerController::OnSwapTurretCannon(const FInputActionValue& val)
{
	if (IsValid(m_ControlledTower))
	{
		const float swapValue = val.Get<float>();
		if (swapValue != 0)
			m_ControlledTower->OnSwapTurret(swapValue);
	}	
}
