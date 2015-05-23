// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
/**
*
*/
#include "ClickEventListener.generated.h"

UINTERFACE()
class UClickEventListener : public UInterface
{

	GENERATED_UINTERFACE_BODY()
};

class IClickEventListener
{
	GENERATED_IINTERFACE_BODY()

	virtual void OnClick(class UPrimitiveComponent * Comp) = 0;

	virtual void OnWorkerInputTouchBegin(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp) = 0;

	virtual void OnWorkerInputTouchEnd(const ETouchIndex::Type FingerIndex, class UPrimitiveComponent * Comp) = 0;
};