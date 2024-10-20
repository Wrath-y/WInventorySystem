// Copyright Epic Games, Inc. All Rights Reserved.

#include "WInventorySystemGameMode.h"
#include "WInventorySystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWInventorySystemGameMode::AWInventorySystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
