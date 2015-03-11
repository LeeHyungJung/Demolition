#include "DemolitionPrivate.h"
#include "PaperFlipbookComponent.h"

#include "DemolitionPaperBlock.h"

ADemolitionPaperBlock::ADemolitionPaperBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	initSprite(ObjectInitializer);
	setApplyFallingAttr(true);
	CollisionSetup();
}

void ADemolitionPaperBlock::CollisionSetup()
{
	GetBaseColisionBox()->InitBoxExtent(FVector(30.f, 30.f, 30.f));
	GetBaseColisionBox()->SetCollisionProfileName("Custom");
	GetBaseColisionBox()->SetCollisionObjectType(COLLISION_BLOCK);
	GetBaseColisionBox()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	GetBaseColisionBox()->SetCollisionResponseToChannel(COLLISION_PLAYERMOVEMENT, ECollisionResponse::ECR_Ignore);
	GetBaseColisionBox()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics, true);
}

void ADemolitionPaperBlock::initSprite(const FObjectInitializer& ObjectInitializer)
{
	// Setup the assets
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> DemolitionAnimationAsset;
		ConstructorHelpers::FObjectFinderOptional<UPaperFlipbook> IdleAnimationAsset;
		FConstructorStatics()
			: DemolitionAnimationAsset(TEXT("/Game/Sprites/RunningAnimation.RunningAnimation"))
			, IdleAnimationAsset(TEXT("/Game/Sprites/IdleAnimation.IdleAnimation"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;
	IdleAnimation = ConstructorStatics.IdleAnimationAsset.Get();
	DemolitionAnimation = ConstructorStatics.DemolitionAnimationAsset.Get();
	Sprite = ObjectInitializer.CreateDefaultSubobject<UPaperFlipbookComponent>(this, "SpriteComponent");
	Sprite->AttachTo(GetBaseColisionBox());
	Sprite->SetFlipbook(IdleAnimation);
}

void ADemolitionPaperBlock::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateAnimation(DeltaSeconds);
}

void ADemolitionPaperBlock::UpdateAnimation_Implementation(float DeltaSeconds)
{
	if (IsBeingDemolition())
	{
		if (GetSprite()->GetFlipbook() == IdleAnimation)
		{
			GetSprite()->SetFlipbook(DemolitionAnimation);
		}
	}
}

