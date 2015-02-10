// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "DemolitionPrivate.h"
#include "DemolitionGameMode.h"
#include "DemolitionCharacter.h"

ADemolitionGameMode::ADemolitionGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our character
	DefaultPawnClass = ADemolitionCharacter::StaticClass();	
}
