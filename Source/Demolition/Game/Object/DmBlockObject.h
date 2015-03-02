// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DmBaseObject.h"
#include "DmBlockObject.generated.h"
/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmBlockObject : public ADmBaseObject
{
	GENERATED_UCLASS_BODY()

	DEPRECATED_FORGAME(4.6, "CapsuleComponent should not be accessed directly, please use GetCapsuleComponent() function instead. CapsuleComponent will soon be private and your code will not compile.")
	UPROPERTY(Category = Block, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** Name of the CapsuleComponent. */
	static FName BoxComponentName;
	
};
