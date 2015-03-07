// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmPaperBlockObject.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"

FName ADmPaperBlockObject::SpriteComponentName(TEXT("Sprite"));

ADmPaperBlockObject::ADmPaperBlockObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetBox()->SetLockedAxis(ELockedAxis::Y);
	
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, SpriteComponentName);
	Sprite->AlwaysLoadOnClient = true;
	Sprite->AlwaysLoadOnServer = true;
	Sprite->bOwnerNoSee = false;
	Sprite->bAffectDynamicIndirectLighting = true;
	Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	Sprite->AttachParent = GetBox();
	static FName CollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
	Sprite->SetCollisionProfileName(CollisionProfileName);
	Sprite->bGenerateOverlapEvents = false;

	GetSprite()->AttachTo(RootComponent);
	
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> RunningAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		FConstructorStatics()
			: RunningAnimationAsset(TEXT("/Game/Sprites/RunningAnimation.RunningAnimation"))
			, IdleAnimationAsset(TEXT("/Game/Sprites/IdleAnimation.IdleAnimation"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();

	GetSprite()->SetFlipbook(IdleAnimation);

}

void ADmPaperBlockObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}


