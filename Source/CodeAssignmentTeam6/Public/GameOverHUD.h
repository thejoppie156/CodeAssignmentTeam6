// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverHUD.generated.h"

/**
 * 
 */
UCLASS()
class CODEASSIGNMENTTEAM6_API UGameOverHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnInitialized() override;

	void InitializeText();

	UFUNCTION()
	void OnClickRetry();

	UFUNCTION()
	void OnClickQuit();

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> m_GameOverText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> m_RetryButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> m_QuitButtonText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UButton> m_QuitButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UButton> m_RetryButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UCanvasPanel > m_Canvas;
};
