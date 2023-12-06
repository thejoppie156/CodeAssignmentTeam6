// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverHUD.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameOverHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	InitializeText();
}

void UGameOverHUD::InitializeText()
{
	if (IsValid(m_GameOverText))
		m_GameOverText->SetText(FText::FromString(TEXT("Game Over")));

	if (IsValid(m_RetryButtonText))
		m_RetryButtonText->SetText(FText::FromString(TEXT("Retry")));

	if (IsValid(m_QuitButtonText))
		m_QuitButtonText->SetText(FText::FromString(TEXT("Quit")));

	if (IsValid(m_RetryButton))
		m_RetryButton->OnClicked.AddDynamic(this, &UGameOverHUD::OnClickRetry);

	if (IsValid(m_QuitButton))
		m_QuitButton->OnClicked.AddDynamic(this, &UGameOverHUD::OnClickQuit);

}

void UGameOverHUD::OnClickRetry()
{	
	UGameplayStatics::OpenLevel(GetWorld(), *UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void UGameOverHUD::OnClickQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), 0,EQuitPreference::Quit,false);
}
