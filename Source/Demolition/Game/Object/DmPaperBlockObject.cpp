// Fill out your copyright notice in the Description page of Project Settings.

#include "DemolitionPrivate.h"
#include "DmPaperBlockObject.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"

FName ADmPaperBlockObject::SpriteComponentName(TEXT("Sprite"));

ADmPaperBlockObject::ADmPaperBlockObject(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, SpriteComponentName);
	GetSprite()->SetSimulatePhysics(true);
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


