// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerCannonBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CODEASSIGNMENTTEAM6_API UTowerCannonBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTowerCannonBase();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	

	UPROPERTY(EditAnywhere)
	float m_RotationSpeed;
	UPROPERTY(EditAnywhere)
	float m_FireRate;
	UPROPERTY(EditAnywhere)
	int m_Damage;
	
	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UTurretDataAsset* TDataAsset;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Fire();

	constexpr float GetRotationSpeed() const;
	constexpr float GetFireRate() const;
	constexpr int GetDamage() const;
	const TObjectPtr<class TurretDataAsset> GetTurretData() const;

	float m_FireRateTimer;
};
