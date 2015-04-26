// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "DemolitionGameMode.h"
#include "DemolitionPlayerController.h"

ADemolitionGameMode::ADemolitionGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// no pawn by default
	DefaultPawnClass = NULL;
	// use our own player controller class
	PlayerControllerClass = ADemolitionPlayerController::StaticClass();
}


