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
	
	UPROPERTY(EditAnywhere)
	float m_WindUpTimer;
	float m_WindUpTime;

};
