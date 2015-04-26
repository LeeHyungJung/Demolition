// Fill out your copyright notice in the Description page of Project Settings.

#include "Demolition.h"
#include "DemolitionPlayerController.h"

ADemolitionPlayerController::ADemolitionPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

