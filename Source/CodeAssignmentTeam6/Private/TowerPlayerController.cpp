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
	InputMapping(nullptr)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ATowerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMapping, 0);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InputActions->Shoot, ETriggerEvent::Triggered, this, &ATowerPlayerController::OnShoot);

		EnhancedInputComponent->BindAction(InputActions->SwapTurretCannon, ETriggerEvent::Started, this, &ATowerPlayerController::OnSwapTurretCannon);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Input Created!"));
	}
}

void ATowerPlayerController::OnShoot()
{
	ATowerBase* ControlledTower = Cast<ATowerBase>(GetPawn());
	if (ControlledTower != nullptr)
	{
		ControlledTower->OnShoot();
	}
}

void ATowerPlayerController::OnSwapTurretCannon(const FInputActionValue& val)
{
	ATowerBase* ControlledTower = Cast<ATowerBase>(GetPawn());
	if (ControlledTower != nullptr)
	{
		const float swapValue = val.Get<float>();
		if (swapValue != 0)
		{
			ControlledTower->OnSwapTurret(swapValue);
		}

	}
	
}
