// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class CODEASSIGNMENTTEAM6_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealth(float currentHealth, float maxHealth);

	void AddScore(int score);

protected:
	void Construct(const class FArguments& InArgs);
	
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UProgressBar> m_HealthBar;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> m_ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> m_HealthText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> m_Canvas;

	UPROPERTY()
	int Score;
};
