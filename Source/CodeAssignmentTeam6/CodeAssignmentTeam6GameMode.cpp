// Copyright Epic Games, Inc. All Rights Reserved.

#include "CodeAssignmentTeam6GameMode.h"
#include "CodeAssignmentTeam6PlayerController.h"
#include "CodeAssignmentTeam6Character.h"
#include "UObject/ConstructorHelpers.h"

ACodeAssignmentTeam6GameMode::ACodeAssignmentTeam6GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ACodeAssignmentTeam6PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}