// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UPlayerHUD::SetHealth(float currentHealth, float maxHealth)
{
	if (m_HealthBar && m_HealthText)
	{
		FString text = FString::Printf(TEXT("%i/%i"), (int)currentHealth,(int)maxHealth);
		m_HealthText->SetText(FText::FromString(text));
		m_HealthBar->SetPercent(currentHealth / maxHealth);
	}
}

void UPlayerHUD::AddScore(int score)
{
	Score += score;

	if (m_ScoreText)
	{
		//FString::Printf(TEXT("Tower Hit for: %f amount of damage"), Score);
		FString text = FString::Printf(TEXT("Score: %i"), Score);
		m_ScoreText->SetText(FText::FromString(text));
	}
}

void UPlayerHUD::Construct(const FArguments& InArgs)
{
	
}

void UPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Score = 0;
}

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	if (m_ScoreText)
	{
		m_ScoreText->SetText(FText::FromString(TEXT("Score: 0")));
	}
	//bind delegates
	//defaul appearance
	//change widget to WBP_

}
