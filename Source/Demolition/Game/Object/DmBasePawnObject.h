// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Game/Object/Attr/DmObjectAttr.h"
#include "DmBasePawnObject.generated.h"

class UDmObjectAttr;
/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmBasePawnObject : public APawn
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attr)
	UDmObjectAttr * Attr;

	UFUNCTION(BlueprintNativeEvent)
	void OnTargeted(const UDmObjectAttr * _Attr);

};
