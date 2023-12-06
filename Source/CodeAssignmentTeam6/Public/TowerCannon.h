// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerCannon.generated.h"

UCLASS()
class CODEASSIGNMENTTEAM6_API ATowerCannon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerCannon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float m_RotationSpeed;	
	UPROPERTY(EditAnywhere)
	int m_Damage;
	UPROPERTY(EditAnywhere)
	float m_FireRate;
	float m_FireRateTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<UStaticMeshComponent> TurretCannonMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<USceneComponent> ProjectileSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> m_ProjectileToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<USceneComponent> TurretCannonPivot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tower")
	TObjectPtr<class ATowerBase> TowerBase;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Fire();
	virtual void OnMouseReleased();

	void LookAtMouse();

	constexpr float GetRotationSpeed() const;
	constexpr float GetFireRate() const;
	constexpr int GetDamage() const;
	const TObjectPtr<class TurretDataAsset> GetTurretData() const;

	void HideInGame(bool hide);
};
