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

	void OnShoot();
	void OnSwapTurret(float val);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	int m_MaxHealth;
	UPROPERTY(EditAnywhere)
	int m_Health;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<UPrimitiveComponent> TurretBase;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<class UTowerCannonBase> TowerCannonComponent;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	//TObjectPtr<UPrimitiveComponent> TurretCannon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<USceneComponent> TurretCannonAttachPoint;
	UPROPERTY(EditAnywhere)
	TObjectPtr<APlayerController> m_PlayerController;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	//TObjectPtr<USceneComponent> ProjectileSpawn;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	//TSubclassOf<class AProjectile> m_ProjectileToSpawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UPlayerHUD> m_PlayerHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UUserWidget> m_PlayerHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class UGameOverHUD> m_GameOverHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TSubclassOf<class UGameOverHUD> m_GameOverHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TObjectPtr<class ATowerCannon> m_TurretCannon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TArray<TSubclassOf<class ATowerCannon>> m_TowerCannonsToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TArray<class ATowerCannon*> Towers;

	int m_TowersIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;	

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	const TObjectPtr<class UPlayerHUD> GetPlayerHUD() const;
};