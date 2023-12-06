// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBaseCharacter.generated.h"

UCLASS()
class CODEASSIGNMENTTEAM6_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TObjectPtr<class ATowerBase> Tower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UStaticMeshComponent> EnemyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_MoveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	int m_ScoreAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float m_AttackRate;
	float m_AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<class AWaveManager> m_WaveManager;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Attack();
	void Init(int health, int damage, float moveSpeed, float attackRange, class AWaveManager* waveManager);
};
