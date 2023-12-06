// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"

void UPlayerHUD::SetHealth(float currentHealth, float maxHealth)
{
	if (m_HealthBar)
	{
		m_HealthBar->SetPercent(currentHealth / maxHealth);
	}
}

void UPlayerHUD::SetScore(int score)
{
	if (m_ScoreText)
	{
		//FText text = 
		m_ScoreText->SetText(FText::FromString(TEXT("Score: 1")));
	}
}

void UPlayerHUD::Construct(const FArguments& InArgs)
{

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
