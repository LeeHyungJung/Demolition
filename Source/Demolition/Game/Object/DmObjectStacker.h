// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DmBasePawnObject.h"
#include "DmObjectStacker.generated.h"
/**
 * 
 */
UCLASS()
class DEMOLITION_API ADmObjectStacker : public ADmBasePawnObject
{
	GENERATED_UCLASS_BODY()
	
	void OnTargeted_Implementation(const UDmObjectAttr * _Attr) override;
};
