// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/**
 * 
 */
#include "ObjectGenerateListener.generated.h"

UINTERFACE()
class UObjectGenerateListener : public UInterface
{

	GENERATED_UINTERFACE_BODY()
};

class IObjectGenerateListener
{
	GENERATED_IINTERFACE_BODY()

	virtual void OnCreatedNode(AActor * node) = 0;
};