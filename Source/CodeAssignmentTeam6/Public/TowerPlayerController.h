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
	void OnShoot();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputConfigData* InputActions;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	TObjectPtr<class UInputMappingContext> InputMapping;
};
