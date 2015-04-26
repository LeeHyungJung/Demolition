// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DemolitionPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMOLITION_API ADemolitionPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ADemolitionPlayerController(const FObjectInitializer& ObjectInitializer);
};
