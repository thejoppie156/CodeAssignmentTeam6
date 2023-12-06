// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TowerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CODEASSIGNMENTTEAM6_API ATowerPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATowerPlayerController();	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void OnShoot();
	void OnShootReleased();
	void OnSwapTurretCannon(const struct FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputConfigData* InputActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputMappingContext> InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<class ATowerBase> m_ControlledTower;
};
