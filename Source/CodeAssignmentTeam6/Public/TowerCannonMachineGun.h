// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerCannon.h"
#include "TowerCannonMachineGun.generated.h"

/**
 * 
 */
UCLASS()
class CODEASSIGNMENTTEAM6_API ATowerCannonMachineGun : public ATowerCannon
{
	GENERATED_BODY()
public:
	ATowerCannonMachineGun();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Fire() override;
	virtual void Reset() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	float m_IncreaseFireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	float m_MaxFireRate;
	float m_BaseFireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tower")
	float m_WindUpTimer;
	float m_WindUpTime;
};
