// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TowerBase.generated.h"

UCLASS()
class CODEASSIGNMENTTEAM6_API ATowerBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void LookAtMouse();
	virtual void Attack();

	UPROPERTY(EditAnywhere)
	int m_MaxHealth;
	UPROPERTY(EditAnywhere)
	int m_Health;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> TurretPosition;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPrimitiveComponent> TurretBase;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UTowerCannonBase> ACTurretCannon;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPrimitiveComponent> TurretCannon;
	UPROPERTY()
	TObjectPtr<APlayerController> m_PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
