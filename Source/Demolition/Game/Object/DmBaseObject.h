// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Game/Object/Attr/DmObjectAttr.h"
#include "DmBaseObject.generated.h"

/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmBaseObject : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attr)
	UDmObjectAttr * Attr;
};
