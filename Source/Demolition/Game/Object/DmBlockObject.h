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

	/** Name of the Box. */
	static FName BoxComponentName;

	UPROPERTY(Category = Box, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxComponent;

	/** Returns Sprite subobject **/
	FORCEINLINE class UBoxComponent* GetBox() const { return BoxComponent; }
};
