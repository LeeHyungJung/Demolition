// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmBlockObject.h"
#include "Components/BoxComponent.h"

FName ADmBlockObject::BoxComponentName(TEXT("CollisionBox"));

ADmBlockObject::ADmBlockObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(ADmBlockObject::BoxComponentName);
	BoxComponent->InitBoxExtent(FVector(30.f, 30.f, 30.f));

	static FName CollisionProfileName(TEXT("Block"));
	BoxComponent->SetCollisionProfileName(CollisionProfileName);

	BoxComponent->CanCharacterStepUpOn = ECB_No;
	BoxComponent->bShouldUpdatePhysicsVolume = true;
	BoxComponent->bCheckAsyncSceneOnMove = false;
	BoxComponent->bCanEverAffectNavigation = false;
	RootComponent = BoxComponent;
}

