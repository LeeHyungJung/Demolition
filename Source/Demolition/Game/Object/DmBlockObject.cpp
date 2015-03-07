// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmBlockObject.h"
#include "Components/BoxComponent.h"
#include "Engine/CollisionProfile.h"

FName ADmBlockObject::BoxComponentName(TEXT("CollisionBox"));

ADmBlockObject::ADmBlockObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(ADmBlockObject::BoxComponentName);
	GetBox()->InitBoxExtent(FVector(30.f, 30.f, 30.f));

	static FName CollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	GetBox()->SetCollisionProfileName(CollisionProfileName);

	GetBox()->CanCharacterStepUpOn = ECB_Yes;
	GetBox()->bShouldUpdatePhysicsVolume = true;
	GetBox()->bCheckAsyncSceneOnMove = false;
	GetBox()->bCanEverAffectNavigation = false;
	GetBox()->SetSimulatePhysics(true);
	GetBox()->SetEnableGravity(true);
	
	RootComponent = GetBox();

	HP = 10;
}

void ADmBlockObject::OnTargeted_Implementation(const UDmObjectAttr * _Attr)
{
	HP--;

	if (HP <= 0)
	{
		Destroy();
	}
}